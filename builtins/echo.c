/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/12 00:27:33 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void    check_args(t_input *input)
{
    int i = 0;
    while (input->cmd[++i])
    {
        if (!ft_strncmp(input->cmd[i], "-n", 2))
        {
            int x = -1;
            int count = 0;
            while (input->cmd[i][++x])
            {
                if (ft_strchr(&input->cmd[i][x], 'n'))
                {
                    printf(".%s\n", input->cmd[i]);
                    i++;
                    count++;
                }

            }
            if ((count + 2) == (int)ft_strlen(input->cmd[i]))
            {
                printf("hahowa%s\n", input->cmd[i]);
            }
        }
    }
}

void    echo(t_input *input, char **env)
{
    int i = 1;

    check_args(input);
    while (input->cmd[i])
    {
        if (input->cmd[i][0] == '$' && input->cmd[i][1] == '?')
        {
            input->cmd[i] = ft_itoa(g_var);
        }
        i++;
    }
    exec(input, env);
    g_var = 0;
}
