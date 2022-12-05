/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/05 21:25:43 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	heredoc_manager(t_progres ptr, int fd[2], char *delim)
{
	char *str;

	printf("hahowa bda ->%s<-\n", delim);
	ptr.input = readline(">");
	str = heredoc(&ptr);
	while (str && ft_strncmp(delim, str, ft_strlen(delim) + 1))
	{
		if (!str)
			str = delim;
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		ptr.i = 0;
		ptr.input = readline(">");
		str = heredoc(&ptr);
	}
	close(fd[1]);
	return (fd[0]);
}

int	ft_heredoc(char *s, char **env)
{
	int p[2];
	t_progres	ptr;

	ptr.i = 0;
	ptr.envp = env;
	if (pipe(p) == -1)
	{
		perror("anass : "); // must set 1 to the exit value
		return -1;
	}
	signal(SIGQUIT, SIG_IGN);
	return (heredoc_manager(ptr, p, s));
}

int    is_builtin(t_input*input)
{
	char *built_in[5] = {
        "cd", "env", "export", "unset", "echo"
    };
	int i = 5;
	while (--i >= 0)
	{
		if (ft_strncmp(input->cmd[0], built_in[i],
        	ft_strlen(built_in[i]) + 1) == 0)
		{
			return i;
		}
	}
	return i;
}

void redic_builtin(t_input *input, char **env)
{
	int in = 0;
	int out = 1;
	int in_fd = dup(STDIN_FILENO);
	int out_fd = dup(STDOUT_FILENO);
	in = get_in(input, in, env);
	out = get_out(input, out);
	if (in)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	execute_builtin(input, env, is_builtin(input));
	if (in)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out != 1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void    ft_redic(t_input *input, char **env)
{
	int in = 0;
	int out = 1;
	int status;
	if (is_builtin(input) == NOT_BUILT_IN)
	{
		int pid = fork();
		if (pid == 0 )
		{
    	    signal(2, SIG_DFL);
    	    signal(SIGQUIT, SIG_DFL);
			in = get_in(input, in, env);
			out = get_out(input, out);
			if (in == -1 || out == -1)
			{
				perror("minishell");
				exit(1);
			}
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
			exec_in_child(input, env);
		}
		else
		{
        	waitpid(pid, &status, 0);
        	if (WIFEXITED(status))
        	    g_var = WEXITSTATUS(status);
        	else
        	    g_var = 1;
		}
	}
	else
		redic_builtin(input, env);
}
