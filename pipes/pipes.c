/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:37:21 by an4ss             #+#    #+#             */
/*   Updated: 2022/10/29 17:34:17 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void    exec_pipes(t_input *tmp, int fd[2], int in, int out, char **env)
{
	dup2(in, STDIN_FILENO);
	if (tmp->pipe && tmp->redirrections && out != 1)
		dup2(out, STDOUT_FILENO);
	else if (tmp->pipe && out == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	else
		dup2(out, STDOUT_FILENO);
	exec_cmds(tmp, env);
}

void get_in_out(t_input *tmp, int fd_in ,int fd_out)
{
  	t_redirect *tmp1;
	tmp1 = tmp->redirrections;
    fd_out = 1;
	while (tmp1)
	{
		if (tmp1->type == '<')
			fd_in = tmp1->fd;
		else
			fd_out = tmp1->fd;
		tmp1 = tmp1->next;
	}
    printf("in:%d\nout:%d\n", fd_in , fd_out);
}

void ft_pipes(t_input *input, char **env)
{
	t_input *tmp;
	
	tmp = input;
	int in = 0;
	int out = 1;
	while (tmp)
	{
    	t_redirect *tmp1;
		tmp1 = tmp->redirrections;
    	out = 1;
		while (tmp1)
		{
			if (tmp1->type == '<')
				in = tmp1->fd;
			else
				out = tmp1->fd;
			tmp1 = tmp1->next;
		}
		printf("in:%d\nout:%d\n", in , out);
		if (in == -1 || out == -1)
		{
			g_var = 1;
			perror("minishell");
			return ;
		}
		int fd[2];
		pipe(fd);
    	int pid = fork();
		if (pid == 0)
			exec_pipes(tmp, fd, in, out, env);
		else
		{
			close(fd[1]);
			in = fd[0];
			wait(&pid);
    		g_var = pid >> 8;
		}
        tmp = tmp->next;
	}
}

