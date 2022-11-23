/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:37:21 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/22 18:31:54 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"


int	get_in(t_input *tmp, int fd_in, char **env)
{
  	t_redirect *tmp1;
	tmp1 = tmp->redirrections;
	while (tmp1)
	{
		if (tmp1->type == '<' && !tmp1->delimiter)
			fd_in = tmp1->fd;
		else if (tmp1->type == '<' && tmp1->delimiter)
			fd_in = ft_heredoc(tmp1->delimiter, env);
		tmp1 = tmp1->next;
	}
		printf("in>%d\n", fd_in);
	return fd_in;
}

int get_out(t_input *tmp, int fd_out)
{
  	t_redirect *tmp1;
	tmp1 = tmp->redirrections;
    fd_out = 1;
	while (tmp1)
	{
		if (tmp1->type == '>' && !tmp1->delimiter)
			fd_out = tmp1->fd;
		tmp1 = tmp1->next;
	}
	printf("out>%d\n", fd_out);
	return fd_out;
}

void	pipes_manager(t_input *tmp, int fd[2], int in, int out, char **env)
{
	dup2(in, STDIN_FILENO);
	if (tmp->pipe && tmp->redirrections && out != 1)
		dup2(out, STDOUT_FILENO);
	else if (tmp->pipe && out == 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(out, STDOUT_FILENO);
	if (in != 0)
		close(in);
	close_all(fd);
	exec_cmds(tmp, env);
}

int	exec_pipes(t_input *tmp, int in, int out, int fd[2], char **env)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		signal(2, SIG_DFL);
		in = get_in(tmp, in, env);
		out = get_out(tmp, out);
		if (in == -1 || out == -1)
		{
			perror("minishell");
			exit(1) ;
		}
		pipes_manager(tmp, fd, in, out, env);
	}
	return pid;
}

void ft_pipes(t_input *input, char **env)
{
	t_input *tmp;
	int fd[2];
	int i = 0;
	int in = 0;
	int out = 1;
	
	tmp = input;
	int *pid = malloc(sizeof(int) * 3);
	ft_memset(fd, -1, sizeof(int)*2);
	while (tmp)
	{
		pipe(fd);
		pid[i] = exec_pipes(tmp, in , out, fd, env);
		if (in != 0)
			close(in);
		in = fd[0];
		fd[0] = -1;
		close_all(fd);
		i++;
        tmp = tmp->next;
	}
	wait_all(pid, i);
}
