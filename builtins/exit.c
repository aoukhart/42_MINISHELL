/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:54:51 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/17 01:30:42 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	check_alpha(char *cmd)
{
	int	i;

	i = -1;
	if (cmd[0] == '-' && ft_atoi(cmd + 1) > 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(cmd));
	}
	while (cmd[++i])
	{
		if (!ft_isdigit(cmd[i]))
			return (1);
	}
	return (0);
}

void	ft_exit(t_input *input, t_progres *progress)
{
	if (input->cmd[1] && check_alpha(input->cmd[1]))
	{
		g_var = 255;
		ft_putstr_fd(input->cmd[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free1(progress, input);
		exit(g_var);
	}
	else if (input->cmd[1] && !check_alpha(input->cmd[1]))
	{
		if (ft_len(input->cmd) > 2)
		{
			g_var = 1;
			printf("exit\n");
			ft_putstr_fd(input->cmd[0], 2);
			ft_putstr_fd(": too many arguments\n", 2);
		}
		else
		{
			printf("exit\n");
			g_var = ft_atoi(input->cmd[1]);
			ft_free1(progress, input);
			exit(g_var);
		}
	}
}
