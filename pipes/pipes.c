/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:37:21 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/14 14:53:22 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void pipes_manager(t_input *tmp, int fd[3], int out, t_progres *progress)
{
	
	dup2(fd[2], STDIN_FILENO);
	if (tmp->pipe && tmp->redirrections && out != 1)
		dup2(out, STDOUT_FILENO);
	else if (tmp->pipe && out == 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(out, STDOUT_FILENO);
	if (fd[2] != 0)
		close(fd[2]);
	close_all(fd);
	if (is_builtin(tmp) == NOT_BUILT_IN)
		exec_in_child(tmp, progress->envp);
	else
	{
		execute_builtin(tmp, progress, is_builtin(tmp));
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

void	check_error(int in, int out)
{
	if (in == -1 || out == -1)
	{
		perror("minishell error fd wayliiii");
		exit(1);
	}
	else if (in == -2 || out == -2)
	{
		ft_putstr_fd("minishell: ambigious redirect\n", 2);
		exit(1);
	}
}

int exec_pipes(t_input *tmp, int fd[3], t_progres *progress, int index)
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
		check_error(fd[2], out);
		pipes_manager(tmp, fd, out, progress);
	}
	return pid;
}

int pipes_len(t_input *input)
{
	int i = 0;
	t_input *tmp;
	tmp = input;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return i;
}

int	*loop_exec_pipes(t_input *input, int fd[3], t_progres *progress)
{
	int i = 0;
	int *pid ;
	pid = malloc(sizeof(int) * pipes_len(input));
	while (input)
	{
		pipe(fd);
		pid[i] = exec_pipes(input, fd, progress, i);
		if (fd[2] != 0)
			close(fd[2]);
		fd[2] = fd[0];
		fd[0] = -1;
		close_all(fd);
		i++;
		input = input->next;
	}
	wait_all(pid, i);
	free(pid);
	return fd;
}

void ft_pipes(t_input *input, t_progres *progress)
{
	t_input *tmp;
	int fd[3];
	int i;
	int *pid;
	i = 0;
	tmp = input;
	pid = malloc(sizeof(int) * pipes_len(input));
	ft_memset(fd, -1, sizeof(int) * 3);
	fd[2] = 0;
	if (execute_heredocs(input, progress->envp))
	{
		g_var = 1;
		return;
	}
	loop_exec_pipes(tmp, fd, progress);
	wait_all(pid, i);
	free(pid);
}
