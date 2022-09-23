#include "minishell.h"

void	execute_1(int pipe[], char **cmd, char **envp)
{
	char	*path;

	close(pipe[0]);

    dup(STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	path = get_path(cmd, envp);
	execve(path, cmd, envp);
	perror("SOMETHING WENT WRONG !!");
	exit(127);
}

void	execute_2(int pipe[], char **cmd, char **envp)
{
	char	*path;

	int output_fd = open("tst", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	close(pipe[1]);
	dup2(pipe[0], STDIN_FILENO);
    dup2(output_fd ,STDOUT_FILENO);
	path = get_path(cmd, envp);
	execve(path, cmd, envp);
	perror("SOMETHING WRONG !!");
	exit(127);
}

void	exec_cmd1(int fd[], char *cmd, char **env)
{
	char	**cmd_f;
	char	*path;
	int		i;


	cmd_f = ft_split(cmd, ' ');
	path = get_path(cmd_f, env);
	if (!path)
		ft_free(cmd_f);
	i = fork();
	if (i == -1)
	{
		perror("SOMETHING WENT WRONG !!");
		exit(127);
	}
	if (i == 0)
		execute_1(fd, cmd_f, env);
    printf("cmd lwla\n");
}

void	exec_cmd2(int fd[], char *cmd, char **env)
{
	char	**cmd_f;
	char	*path;
	int		i;

	cmd_f = ft_split(cmd, ' ');
	path = get_path(cmd_f, env);
	if (!path)
		ft_free(cmd_f);
	i = fork();
	if (i == -1)
	{
		perror("SOMWTHING WENT WRONG !!");
		exit(127);
	}
	if (i == 0)
		execute_2(fd, cmd_f, env);
    printf("cmd tania\n");


}

void    exec_pipe(char **cmd, char **env)
{
    (void)env;
    printf("--->%s\n", cmd[0]);
    printf("--->%s\n", cmd[1]);
    int fd[2];
    if (pipe(fd) != 0)
	{
	    perror("SOMETHING WENT WRONG !!");
		exit(EXIT_FAILURE);
	}
	exec_cmd1(fd, cmd[0], env);
	exec_cmd2(fd, cmd[1], env);
    close(fd[1]);
    close(fd[0]);
    rl_on_new_line();
    return ;
}

void    execute(char *s, char **env)
{
    char **cmd;
    
    if (ft_strchr(s, '|'))
    {
        cmd = ft_split(s, '|');
        exec_pipe(cmd, env);
    }
    else
    {
        cmd = ft_split(s, ' ');
        if (!cmd[0])
            return;
        check_builtins(cmd, env);
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
                exit(0);
            if(s[0] == '\0')
            {
                free(s);
                continue;
            }
            add_history(s);
            execute(s, env);

            free(s);
        }
    }
    return 0;
}