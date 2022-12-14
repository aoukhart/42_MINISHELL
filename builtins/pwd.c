/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:45:51 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/14 07:20:49 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void pwd(t_input *input, t_progres *progress)
{
    (void)input;
    (void)progress;
    char *s= getcwd(0,0);
    printf("%s\n",s);
    free(s);
}