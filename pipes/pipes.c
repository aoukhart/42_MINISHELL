/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:37:21 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/15 09:36:41 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"


int	get_in(t_input *tmp, int fd_in, int fd, char **env)
{
  	t_redirect *tmp1;
	tmp1 = tmp->redirrections;
	//if (fd > 0)
	//{
		printf("*%d*\n",fd);
	//	return fd;
	//}
	while (tmp1)
	{
		if (tmp1->type == '<' && !tmp1->delimiter)
			fd_in = tmp1->fd;
		else if (tmp1->type == '<' && tmp1->delimiter)
			fd_in = ft_heredoc(tmp1->delimiter, env);
		tmp1 = tmp1->next;
	}
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
    printf("->out:%d\n", fd_out);
	return fd_out;
}

void	pipes_manager(t_input *tmp, int fd[3], int in, int out, char **env)
{
	if (fd[2] != -1)
		dup2(fd[2], STDIN_FILENO);
	else
		dup2(in, STDIN_FILENO);

	if (tmp->pipe && tmp->redirrections && out != 1)
		dup2(out, STDOUT_FILENO);
	else if (tmp->pipe && out == 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(out, STDOUT_FILENO);
	if (fd[2] != -1)
		close(fd[2]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[0] != -1)
		close(fd[0]);
	exec_cmds(tmp, env);
}

//int	exec_pipes(t_input *tmp, int in, int out, char **env)
//{
//	//printf("in: %d\nout: %d\n", in ,out);
//	
//	int fd[2];
//	int status;
//	pipe(fd);
//	int pid = fork();
//	if (pid == 0)
//	{
//		signal(2, SIG_DFL);
//		in = get_in(tmp, in);
//		out = get_out(tmp, out);
//		if (in == -1 || out == -1)
//		{
//			g_var = 1;
//			perror("minishell");
//			exit(0) ;
//		}	
//		pipes_manager(tmp, fd, in, out, env);
//		
//	}
//	else
//	{
//		wait(&status);
//		close(fd[1]);
//		g_var = status >> 8;
//	}
//		return fd[0];
//}

void ft_pipes(t_input *input, char **env)
{
	t_input *tmp;
	
	tmp = input;
	int fd[3];
	int status;
	int in = 0;
	int out = 1;
	int i = 0;
	g_var = 0;
	int *pid = malloc(sizeof(int) * 3);
	ft_memset(fd, -1, sizeof(int)*3);
	while (tmp)
	{
		pipe(fd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			signal(2, SIG_DFL);
			in = get_in(tmp, in, fd[2], env);
    		printf("->in:%d\n", in);
			out = get_out(tmp, out);
			if (in == -1 || out == -1)
			{
				perror("minishell");
				exit(1) ;
			}
			pipes_manager(tmp, fd, in, out, env);
		}
		else
		{
			if (fd[2] != -1)
				close(fd[2]);
			fd[2] = fd[0];
			if(fd[1] != -1)
				close(fd[1]);
			fd[0] = -1;
			fd[1] = -1;
		}
		i++;
        tmp = tmp->next;
	}
	if (fd[2] != -1)
		close(fd[2]);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[0] != -1)
		close(fd[0]);	
	int y = -1;
	while (pid[++y])
	{
		waitpid(pid[y], &status, 0);
		if ((status >> 8) > g_var)
			g_var = status >> 8;
	}
}

