/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:37:21 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/12 11:01:52 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void pipes_manager(t_input *tmp, int fd[2], int in, int out, char **env)
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
	{
		execute_builtin(tmp, env, is_builtin(tmp));
		exit(0);
	}
}

int execute_heredocs(t_input *input, char **env)
{
	int pid = fork();
	if (pid == 0)
		open_herdoc_file(input, env);
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			return 1;
	}
	return 0;
}

int exec_pipes(t_input *tmp, int fd[3], char **env, int index)
{
	int pid;
	int out = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(2, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		fd[2] = get_in_v2(tmp, fd[2], index);
		out = get_out(tmp, out);
		printf("in>%d\nout>%d\n", fd[2], out);
		if (fd[2] == -1 || out == -1)
		{
			perror("minishell error fd wayliiii");
			exit(1);
		}
		if (fd[2] == -2 || out == -2)
		{
			ft_putstr_fd("minishell: ambigious redirect\n", 2);
			exit(1);
		}
		pipes_manager(tmp, fd, fd[2], out, env);
	}
	return pid;
}

void ft_pipes(t_input *input, char **env)
{
	t_input *tmp;
	int fd[3];
	int i = 0;
	// int in = 0;

	tmp = input;
	int *pid = malloc(sizeof(int) * 3);
	ft_memset(fd, -1, sizeof(int) * 3);
	fd[2] = 0;
	if (execute_heredocs(input, env))
	{
		g_var = 1;
		return;
	}
	while (tmp)
	{
		pipe(fd);
		pid[i] = exec_pipes(tmp, fd, env, i);
		if (fd[2] != 0)
			close(fd[2]);
		fd[2] = fd[0];
		fd[0] = -1;
		close_all(fd);
		i++;
		tmp = tmp->next;
	}
	wait_all(pid, i);
}
