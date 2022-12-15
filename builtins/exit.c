/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:54:51 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/15 06:54:44 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	ft_exit(t_input *input, t_progres *progress)
{
	if (input->cmd[2])
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		g_var = 1;
	}
	else if (input->cmd[1])
		g_var = ft_atoi(input->cmd[1]);
	
	ft_free1(progress, input);
	printf("exit\n");
	exit(g_var);
}
