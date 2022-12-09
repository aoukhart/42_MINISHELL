/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/09 10:51:39 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int    is_builtin(t_input*input)
{
	char *built_in[6] = {
        "cd", "env", "export", "unset", "echo", "pwd"
    };
	int i = 6;
	while (--i >= 0)
	{
		if (ft_strncmp(input->cmd[0], built_in[i],
        	ft_strlen(built_in[i]) + 1) == 0)
		{
			return i;
		}
	}
	return i;
}

void redic_builtin(t_input *input, char **env)
{
	int in = 0;
	int out = 1;
	int in_fd = dup(STDIN_FILENO);
	int out_fd = dup(STDOUT_FILENO);
	in = get_in(input, in);
	out = get_out(input, out);
	if (in == -1 || out == -1)
	{
		perror("minishell");
		exit(1);
	}
	dup_in_out(in, out);
	execute_builtin(input, env, is_builtin(input));
	restore_fd(in, out, in_fd, out_fd);
}


void redic_not_builtin(t_input *input, char **env)
{
	int in = 0;
	int out = 1;
	int pid = fork();
	if (pid == 0)
	{
	    signal(2, SIG_DFL);
	    signal(SIGQUIT, SIG_DFL);
		in = get_in(input, in);
		out = get_out(input, out);
		if (in == -1 || out == -1)
		{
			perror("minishell");
			exit(1);
		}
		dup_in_out(in, out);
		exec_in_child(input, env);
	}
	else
		handle_exit_val(pid);
}

void    ft_redic(t_input *input, char **env)
{
	if (execute_heredocs(input, env))
	{
		g_var = 1;
		return;
	}
	if (is_builtin(input) == NOT_BUILT_IN)
		redic_not_builtin(input, env);
	else
		redic_builtin(input, env);
}
