/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:35:22 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/17 01:57:07 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDE/minishell.h"

void	ctrl_c_handler(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var = 130;
}

void	signals(void)
{
	signal(SIGINT, ctrl_c_handler);
}
