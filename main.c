#include "minishell.h"


void	exec_cmds(int fd[], char **cmd, char **env)
{
	char **cmd1;
	char **cmd2;

	cmd1 = ft_split(cmd[0], ' ');
	cmd2 = ft_split(cmd[1], ' ');
	int i = fork();
	if (i == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (i == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
    	if (ft_strncmp(cmd1[0], "env", 4) == 0)
    	    my_env(env);
    	else if (ft_strncmp(cmd1[0], "export", 7) == 0)
    	    export(cmd1, env);
    	else if (ft_strncmp(cmd1[0], "echo", 5) == 0)
			echo(cmd1, env);
		else
		{
			if (execve(get_path(cmd1, env), cmd1, env) == -1)
        	{
        	    perror("aaaa");
            	exit(127);
        	}
		}
		exit(0);
	}
	else if (i >= 0)
		wait(NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	check_builtins(cmd2, env);
}

void    exec_pipe(char **cmd, char **env)
{
    int fd[2];
    if (pipe(fd) != 0)
	{
	    perror("SOMETHING WENT WRONG !!");
		exit(EXIT_FAILURE);
	}
	exec_cmds(fd, cmd, env);
    close(fd[1]);
    close(fd[0]);
}

void    execute(char *s, char **env)
{
    char **cmd;
    

    cmd = ft_split(s, '|');
	int i = -1;
	while (cmd[++i]);
	--i;
	if (i >= 1)
		exec_pipe(cmd, env);
	else
	{
		char **cmd1 = ft_split(cmd[0], ' ');
    	check_builtins(cmd1, env);
	}
}

int main(int ac, char **av, char **envp)
{
    char *s;
    char **env;
    (void)av;

    if (ac == 1)
    {
        env = init_env(envp);
        while (1)
        {
            signals();
            s = readline("minishell>>");
            if(!s)
			{
				printf("rah khawi\n");
            	exit(0);
			}
            add_history(s);
            execute(s, env);
            //free(s);
        }
    }
    return 0;
}