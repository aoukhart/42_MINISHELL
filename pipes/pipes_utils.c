/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:35:10 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/16 17:11:07 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	close_all(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	fd[0] = -1;
	fd[1] = -1;
}

void	handle_exit_val(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_var = WEXITSTATUS(status);
	else
		g_var = 128 + WTERMSIG(status);
}

void	wait_all(int *pid, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		handle_exit_val(pid[i]);
		i++;
	}
}

int	pipes_len(t_input *input)
{
	int		i;
	t_input	*tmp;

	i = 0;
	tmp = input;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	check_error(int in, int out)
{
	if (in == -1 || out == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		exit(1);
	}
	else if (in == -2 || out == -2)
	{
		ft_putstr_fd("minishell: ambigious redirect\n", 2);
		exit(1);
	}
}
