/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:15:34 by an_ass            #+#    #+#             */
/*   Updated: 2022/12/16 18:07:52 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	check_permission(void)
{
	if (errno == 8)
	{
		ft_putstr_fd("minishell: permission denied\n", 2);
		exit(126);
	}
}

void	exec(t_input *input, t_progres *progress)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed\n");
		return ;
	}
	else if (pid == 0)
	{
		signal(2, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(get_path(input->cmd, progress->envp),
				input->cmd, progress->envp) == -1)
		{
			check_permission();
			ft_putstr_fd(input->cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	else
		handle_exit_val(pid);
}

void	execute_builtin(t_input *input, t_progres *progress, int index)
{
	void	(*fcts[7])(t_input*, t_progres*);

	fcts[0] = cd;
	fcts[1] = my_env;
	fcts[2] = export;
	fcts[3] = unset;
	fcts[4] = echo;
	fcts[5] = pwd;
	fcts[6] = ft_exit;
	fcts[index](input, progress);
}

int	check_error_single_cmd(t_input *input)
{
	if (input->redirrections && (input->redirrections->fd) == -2)
	{
		ft_putstr_fd("minishell: ambigious redirect\n", 2);
		g_var = 1;
		return (0);
	}
	else if (input->redirrections && (input->redirrections->fd) == -1)
	{
		perror("minihell");
		g_var = 1;
		return (0);
	}
	return (1);
}

void	execute_single_cmd(t_input *input, t_progres *progress)
{
	if (execute_heredocs(input, progress->envp))
	{
		g_var = 1;
		return ;
	}
	if (!check_error_single_cmd(input))
		return ;
	if (input->cmd)
	{
		if (input->redirrections)
			exec_redirection(input, progress);
		else
		{
			if (is_builtin(input) == NOT_BUILT_IN)
				exec(input, progress);
			else
				execute_builtin(input, progress, is_builtin(input));
		}
	}
	else
		g_var = 0;
	unlink("minishell_0");
}
