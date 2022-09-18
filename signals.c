/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:35:22 by aoukhart          #+#    #+#             */
/*   Updated: 2022/09/18 04:48:26 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ctrl_c_handler(int sig)
{
    sig = 0;
    // signal(sig, SIG_IGN);
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void signals()
{
    // printf("salam\n");
    signal(SIGINT, ctrl_c_handler);
}