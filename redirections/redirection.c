/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/22 19:22:41 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	ft_heredoc(char *s, char **env)
{
	int p[2];
	char *str;
	if (pipe(p) == -1)
	{
		perror("anass : "); // must set 1 to the exit value
		return -1;
	}
    //signal(2, SIG_DFL);
	str = readline(">");
	while (ft_strncmp(s, str, ft_strlen(s) + 1))
	{
		
		if(str[0] == '$')
		{
			if (ft_chr(env, (str+1)))
				str = ft_chr(env, (str+1));
			else
				str = "\n";
		}
		write(p[1], str, ft_strlen(str));
		write(p[1], "\n", 1);
		str = readline(">");
		if(str == NULL)
		{
			printf("<%s>\n",str);
			str = s;
		}
	}
		close(p[1]);
	printf("sf ra salaw %d\n", p[0]);
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
		int out = get_fd_out(input);
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
