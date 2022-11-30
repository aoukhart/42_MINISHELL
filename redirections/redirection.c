/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/29 21:51:56 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	heredoc_manager(t_progres ptr, int fd[2], char *delim)
{
	char *str;

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

int redic_builtins(t_input *input, char **env)
{
	int in = 0;
	int out = 1;
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
	close(in);
	close(out);
	return (check_builtins_1(input, env) 
   			& check_builtins_2(input, env));
}
void    ft_redic(t_input *input, char **env)
{
	int in = 0;
	int out = 1;
	if (redic_builtins(input, env))
	{
	printf(".\n");
    	int pid = fork();
		if (pid == 0)
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
			//if (in)
			//	close(in);
			if (out != 1)
				close(out);
			exec(input, env);
			exit(0);
		}
		else
		{
			wait(&pid);
			g_var = pid >> 8;
		}
	}
	else
	{
		
	}	
}
