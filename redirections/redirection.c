/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/25 23:29:43 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	ft_heredoc(char *s, char **env)
{
	int p[2];
	char *str;
	t_progres	ptr;

	ptr.i = 0;
	ptr.envp = env;
	if (pipe(p) == -1)
	{
		perror("anass : "); // must set 1 to the exit value
		return -1;
	}
    //signal(2, SIG_DFL);
	ptr.input = readline(">");
	str = heredoc(&ptr);
	while (str && ft_strncmp(s, str, ft_strlen(s) + 1))
	{
		if (!str)
		{
			printf("<%s>\n",str);
			str = s;
		}
		write(p[1], str, ft_strlen(str));
		write(p[1], "\n", 1);

		ptr.i = 0;
		ptr.input = readline(">");
		str = heredoc(&ptr);
	}

	close(p[1]);

	return (p[0]);
}

void    ft_redic(t_input *input, char **env)
{
    int pid = fork();
	//signal(2, SIG_IGN);
	int in = 0;
	int out = 1;
	if (pid == 0)
	{
        signal(2, SIG_DFL);
		in = get_in(input, in, env);
		out = get_out(input, out);
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
		exec_cmds(input, env);
	}
	else
	{
		wait(&pid);
		g_var = pid >> 8;
	}	
}
