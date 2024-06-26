/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/08 15:04:03 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void    echo(t_input *input, char **env)
{
    int i = 1;
    while (input->cmd[i])
    {
        if (input->cmd[i][0] == '$' && input->cmd[i][1] == '?')
        {
            input->cmd[i] = ft_itoa(g_var);
        }
        i++;
    }
    // if (execve(get_path(input->cmd, env), input->cmd, env) == -1)
    // {
    //      perror("mochkila hadi");
    //      exit(127);
    // }
    exec(input, env);
    g_var = 0;
}
