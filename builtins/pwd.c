/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:45:51 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/13 12:10:42 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void pwd(t_input *input, t_progres *progress)
{
    (void)input;
    (void)progress;
   printf("%s\n",getcwd(0,0));
}