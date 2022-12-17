/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/17 00:06:37 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	is_builtin(t_input*input)
{
	char	*built_in[7];
	int		i;

	i = 7;
	built_in[0] = "cd";
	built_in[1] = "env";
	built_in[2] = "export";
	built_in[3] = "unset";
	built_in[4] = "echo";
	built_in[5] = "pwd";
	built_in[6] = "exit";
	while (--i >= 0)
	{
		if (ft_strncmp(input->cmd[0],
				built_in[i], ft_strlen(built_in[i]) + 1) == 0)
		{
			return (i);
		}
	}
	return (i);
}

void	redic_builtin(t_input *input, t_progres *progress)
{
	int	in;
	int	out;
	int	in_fd;
	int	out_fd;

	in = 0;
	out = 1;
	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);
	in = get_in(input, in);
	out = get_out(input, out);
	check_error_main(in, out);
	dup_in_out(in, out);
	execute_builtin(input, progress, is_builtin(input));
	restore_fd(in, out, in_fd, out_fd);
}

void	redic_not_builtin(t_input *input, char **env)
{
	int	in;
	int	out;
	int	pid;

	in = 0;
	out = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(2, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		in = get_in(input, in);
		out = get_out(input, out);
		check_error(in, out);
		dup_in_out(in, out);
		exec_in_child(input, env);
	}
	else
		handle_exit_val(pid);
}

void	exec_redirection(t_input *input, t_progres *progress)
{
	if (is_builtin(input) == NOT_BUILT_IN)
		redic_not_builtin(input, progress->envp);
	else
		redic_builtin(input, progress);
}
