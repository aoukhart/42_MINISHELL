/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:02:22 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/13 02:34:46 by aoukhart         ###   ########.fr       */
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
	if (out == -2 || in == -2) 
	{
		ft_putstr_fd("minishell: ambiguous redirect", 2);
		g_var = 1;
		return;
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
		printf("in>%d\nout>%d\n", in, out);
		if (in == -1 || out == -1)
		{
			perror("minishell");
			exit(1);
		}
		if (out == -2 || in == -2) 
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			exit(1);
		}
		dup_in_out(in, out);
		exec_in_child(input, env);
	}
	else
		handle_exit_val(pid);
}
