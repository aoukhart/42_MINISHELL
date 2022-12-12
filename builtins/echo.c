/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/12 05:55:47 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

// void    handler(t_input *input, )
// {}

void    check_args(t_input *input)
{
    printf("%s\n", input->cmd[0]);
    printf("%s\n", input->cmd[1]);

    int i = 0;
    int count = 0;
    // int len = 0;
    // t_input *tmp;
    // int *fd =;
    // tmp = input;
    // while (tmp->cmd[len])
    // {
    //     len++;
    // }
    // int index = 0;
    // ft_memset(fd , 69, sizeof(int) * len);
    while (input->cmd[++i])
    {
        if (!ft_strncmp(input->cmd[i], "-n", 2))
        {
            printf("%d, %s\n",ft_strncmp(input->cmd[i], "-n", 2), input->cmd[i]);
            int x = 1;
            int c = 0;
            while (input->cmd[i][++x])
            {
                if (ft_strchr(&input->cmd[i][x], 'n'))
                {
                    c++;
                }
                else
                {
                    printf(">%d<\n", count);
                    // handler(input, count);
                    return ;
                }
            }
            if ((c + 2) == (int)ft_strlen(input->cmd[i]))
                count ++;
        }
    }
}

void    echo(t_input *input, char **env)
{
    // int i = 1;

    //check_args(input);
    // while (input->cmd[i])
    // {
    //     if (input->cmd[i][0] == '$' && input->cmd[i][1] == '?')
    //     {
    //         input->cmd[i] = ft_itoa(g_var);
    //     }
    //     i++;
    // }
    exec(input, env);
    g_var = 0;
}
