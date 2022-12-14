/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:54:51 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/13 11:56:34 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void    ft_exit(t_input *input, t_progres *progress)
{
    ft_free1(progress, input);
    exit(g_var);
}