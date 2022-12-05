/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:37:21 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/05 02:19:26 by aoukhart         ###   ########.fr       */
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
		// printf("in>%d\n", fd_in);
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
	// printf("out>%d\n", fd_out);
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
	if (is_builtin(tmp) == NOT_BUILT_IN)
		exec_in_child(tmp, env);
	else
		execute_builtin(tmp, env, is_builtin(tmp));
}

int	get_in_v2(t_input *tmp, int fd_in, int *fd, int index)
{
  	t_redirect *tmp1;
	tmp1 = tmp->redirrections;
	while (tmp1)
	{
		if (tmp1->type == '<' && !tmp1->delimiter)
			fd_in = tmp1->fd;
		else if (tmp1->type == '<' && tmp1->delimiter)
			fd_in = fd[index];
		tmp1 = tmp1->next;
	}
	return fd_in;
}

int	exec_pipes(t_input *tmp, int in, int out, 
	int fd[2], char **env, int *ff, int index)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		signal(2, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		in = get_in_v2(tmp, in, ff, index);
		out = get_out(tmp, out);
		if (in == -1 || out == -1)
		{
			perror("minishell error fd");
			exit(1) ;
		}
		pipes_manager(tmp, fd, in, out, env);
	}
	return pid;
}

int get_line_len(t_input * input)
{
	t_input *tmp;
	int pipe = 0;
	tmp = input;
	while (tmp)
	{
		if (tmp->pipe)
			pipe++;
		tmp = tmp->next;
	}
	return pipe;
}

int	*execute_heredocs(t_input *input, char **env)
{
	int *in_tab;
	int i = 0;
	t_input *tmp;
	t_redirect *redir;
	int len =  get_line_len(input);
	tmp = input;
	in_tab = malloc(sizeof(int)*len);
	ft_memset(in_tab, 0,len*sizeof(int));
	while (i <= len && tmp)
	{
		printf("->%s<-\n", tmp->cmd[0]);
		redir = tmp->redirrections;
		while (redir)
		{
			if (redir->type == '<' && redir->delimiter)
			{
				in_tab[i] = ft_heredoc(redir->delimiter, env);
				printf("fd %d heredoc %d\n", i, in_tab[i]);
			}
			redir = redir->next;
		}
		i++;
		tmp = tmp->next;
	}
	return in_tab;
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
	int *in_redir = execute_heredocs(input, env);
	int x = 0;
	while (x <= get_line_len(input))
	{
		printf("->%d\n", in_redir[x]);
		x++;
	}
	// return ;
	while (tmp)
	{
		pipe(fd);
		pid[i] = exec_pipes(tmp, in , out, fd, env, in_redir, i);
		if (in != 0)
			close(in);
		in = fd[0];
		fd[0] = -1;
		close_all(fd);
		i++;
		printf("g_var = %d\n", g_var);
        tmp = tmp->next;
	}
	wait_all(pid, i);
}
