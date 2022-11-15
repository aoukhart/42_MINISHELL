/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/15 08:52:18 by an4ss            ###   ########.fr       */
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
	}
	//signal(2, SIG_IGN);		
	close(p[1]);
	return (p[0]);
}

void    ft_redic(t_input *input, char **env)
{
    int pid = fork();
	//signal(2, SIG_IGN);
	if (pid == 0)
	{
        signal(2, SIG_DFL);
		int in = get_fd_in(input, env);
		int out = get_fd_out(input);
		//printf("in:%d\nout:%d\n", in , out);
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

int get_fd_in(t_input *input, char **env)
{
    t_redirect *tmp;
    int in = 0;
    tmp = input->redirrections;
    while (tmp)
    {
        if (tmp->type && tmp->type == '<' && !tmp->delimiter)
            in = tmp->fd;
        else if (tmp->type && tmp->type == '<' && tmp->delimiter)
			in = ft_heredoc(tmp->delimiter, env);
        tmp = tmp->next;
    }
	if (in == -1)
    {
        perror("redic");
        g_var = 1;
        exit(EXIT_FAILURE);
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