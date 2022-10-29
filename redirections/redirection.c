/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/10/28 22:39:28 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

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

void    ft_redic(t_input *input, char **env)
{
    int pid = fork();
	signal(2, SIG_IGN);
	if (pid == 0)
	{
        signal(2, SIG_DFL);
		//if (in)
		//{
			int in = get_fd_in(input);
			dup2(in,STDIN_FILENO);
			close(in);
		//}
		//if (out != 1)
		//{
			int out = get_fd_out(input);
			dup2(out,STDOUT_FILENO);
			close(out);
		//}
		exec_cmds(input, env);
	}
	else
	{
		wait(&pid);
		g_var = pid >> 8;
	}	
}

int get_fd_in(t_input *input)
{
    t_redirect *tmp;
    int in = 0;
    tmp = input->redirrections;
    while (tmp)
    {
        if (tmp->type && tmp->type == '<')
        {
            in = tmp->fd;
            if (in == -1)
            {
                perror("redic");
                g_var = 1;
                exit(EXIT_FAILURE);
            }
        }
        tmp = tmp->next;
    }
    return in;
}

int get_fd_out(t_input *input)
{
    t_redirect *tmp;
    int out = 1;
    tmp = input->redirrections;
    while (tmp)
    {
        if (tmp->type && tmp->type == '>')
        {
            out = tmp->fd;
            if (out == -1)
            {
                perror("redic");
                g_var = 1;
                exit(EXIT_FAILURE);
            }
        }
        tmp = tmp->next;
    }
    return out;
}