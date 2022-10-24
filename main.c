#include "minishell.h"

void exec_cmds(char **cmd, char **env)
{

	if (ft_strncmp(cmd[0], "env", 4) == 0)
		my_env(env);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		export(cmd, env);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		echo(cmd, env);
	else
	{
		// exec(cmd, env);
		if (execve(get_path(cmd, env), cmd, env) == -1)
		{
			perror("SOMETHING WENT WRONG !!0");
			exit(127);
		}
	}
	exit(0);
}

void multi_pipes(t_input *input, char **env)
{
	int fd[2];
	t_input *tmp;
	
	tmp = input;
	int in = 0;
	int out = 1;
	while (tmp)
	{
		t_redirect *tmp1;
		tmp1 = tmp->redirrections;
		while (tmp1)
		{
			if (tmp1->type == '<')
				in = tmp1->fd;
			else
				out = tmp1->fd;
			tmp1 = tmp1->next;
		}
		printf("in fd: %d\nout fd: %d\n", in, out);
		pipe(fd);
		int pid = fork();
		if (pid == 0)
		{
			dup2(in, STDIN_FILENO);
			if (tmp->pipe && tmp->redirrections)
				dup2(out, STDOUT_FILENO);
			else if (tmp->pipe)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
			}
			else
				dup2(out, STDOUT_FILENO);
			exec_cmds(tmp->cmd, env);
		}
		else
		{
			close(fd[1]);
			in = fd[0];
			tmp = tmp->next;
			wait(&pid);
		}
	}
}

int	ft_heredoc(char *s)
{
	int p[2];
	int nb = 0;
	char str[256];
	if (pipe(p) == -1)
	{
		perror("anass : "); // must set 1 to the exit value
		return -1;
	}
	int len = ft_strlen(s);
	write(1, ">", 1);
	while ((nb  = read(0, str, 1)) > 0)
	{
		str[nb] = 0;
		//write(1, str, nb);
		if (ft_strncmp(str , s, len) == 0)
		{
			//write(1, &s, nb);

			break;
		}
		write(1, str, nb);
		write(p[1], str, 1);
		write(1, ">", 1);
		
	}
	close(p[1]);
	return (p[0]);
}

int	heredoc_handler(char **cmd)
{
	int j = -1;
	int in_file = 0;
	while (cmd[++j])
	{
		if (ft_strncmp(cmd[j], "<<", 3) == 0)
			break;
	}
	//if (!cmd[j])
	//	return 0;
	char **arr = ft_split(cmd[j], ' ');
	in_file = ft_heredoc(arr[1]);
	int start = -1;
	int end = 0;
	while (cmd[j][++start] != '<' && cmd[j][start + 1] != '<');
	end = start;
	while (cmd[j][++end] != '<');
	end++;
	while(cmd[j][++end] != ' ');
	char *str = ft_substr(cmd[j], 5, ft_strlen(cmd[j]) - 5);
	cmd[j] = ft_strdup(str);
	printf("%sff\n", cmd[0]);
	printf("%sff\n", cmd[1]);
	printf("%sff\n", cmd[2]);
	return (in_file);
}

int handle_in_redic(char **cmd, int fd)
{
	int j = 0;

	while (j)
	{
		if (ft_strchr(cmd[j], '<'))
			break;
		j--;
	}
	//printf("%dd\n", j);
	//if (!cmd[j])
	//	return (fd);
	if (cmd[j] && ft_strchr(cmd[j], '<'))
	{
		int start = -1;
		int end = 0;
		while (cmd[j][++start] != '<');
		char **tmp = ft_split(cmd[j], ' ');
		int i = 0;
		while (tmp[i])
		{
			if (ft_strchr(tmp[i], '<'))
				break;
			i++;
		}
		end = ft_strlen(tmp[i + 1]) + 2 + start;
		char *tmp1;
		char **tmp2;
		tmp2 = ft_split(cmd[j], ' ');
		if (!ft_strncmp(tmp2[0], "<", 1))
			tmp1 = ft_substr(cmd[j], end, end - start);
		else
			tmp1 = ft_substr(cmd[j], 0, start);
		cmd[j] = ft_strdup(tmp1);
		fd = open(tmp[i + 1],O_RDONLY, 0644);
		return (fd);
	}
	return fd;
}

void execute(t_input *input, char **env)
{
	if (!input->redirrections && !input->pipe)
		check_builtins(input, env);
	else if (input->redirrections && !input->pipe)
	{
		int in = get_fd_in(input);
		int out = get_fd_out(input);
		int pid = fork();
    	signal(2, SIG_IGN);
		if (pid == 0)
		{
	        signal(2, SIG_DFL);
			if (in)
			{
				dup2(in,STDIN_FILENO);
				close(in);
			}
			if (out != 1)
			{
				dup2(out,STDOUT_FILENO);
				close(out);
			}
			exec_cmds(input->cmd, env);
		}
		else
			wait(NULL);	
	}
	else if (input->pipe)
	{
		multi_pipes(input, env);
	}
	//char **cmd;
//
	//cmd = ft_split(s, '|');
	//int i = -1;
	//while (cmd[++i])
	//	;
	//--i;
	//if (i >= 1)
	//	exec_pipe(cmd, env, i);
	//else
	//{
	//	char **cmd1 = ft_split(cmd[0], ' ');
	//}
}

int main(int ac, char **av, char **envp)
{
	char *s;
	char **env;
	(void)av;
	t_input *input;
	if (ac == 1)
	{
		env = init_env(envp);
		input = malloc(sizeof(t_input));
		while (1)
		{
			signals();
			s = readline("minishell>>");
			if (!s)
			{
				printf("rah khawi\n");
				exit(0);
			}
			if (!s[0])
			{
				free(s);
				continue;
			}
			add_history(s);
			step_one(s, input, env);
			execute(input, env);
		}
	}
	return 0;
}
