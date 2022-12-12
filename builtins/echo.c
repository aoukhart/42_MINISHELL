/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/12 11:56:55 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

// char **handler(t_input *input, int c)
// {
//     int len = ft_len(input->cmd);
//     char **cmd = malloc((len - c + 1) * sizeof(char *));
//     cmd[0] = "echo";
//     cmd[1] = "-n";
//     int i = 2;
//     printf("%d\n", len - c + 1);
//     int x = len - c + 1;
//     while (i < x)
//     {
//         printf("->%s\n", input->cmd[c]);
//         cmd[i] = input->cmd[c];
//         c++;
//         i++;
//     }
//     return cmd;
// }
// char **check_args(t_input *input)
// {
//     int i = 0;
//     int count = 2;
//     while (input->cmd[++i])
//     {
//         if (!ft_strncmp(input->cmd[i], "-n", 2))
//         {
//             printf("%d, %s\n",ft_strncmp(input->cmd[i], "-n", 2), input->cmd[i]);
//             int x = 1;
//             int c = 0;
//             while (input->cmd[i][++x])
//             {
//                 if (ft_strchr(&input->cmd[i][x], 'n'))
//                     c++;
//                 else
//                 {
//                     printf(">%d<\n", count);
//                     return (handler(input, count));
//                 }
//             }
//             if ((c + 2) == (int)ft_strlen(input->cmd[i]))
//                 count ++;
//         }
//     }
//     printf(">%d<\n", count);
//     return NULL;
// }

void    echo(t_input *input, char **env)
{
    int i = 1;

    // input->cmd = check_args(input);
    while (input->cmd[i])
    {
        if (input->cmd[i][0] == '$' && input->cmd[i][1] == '?')
        {
            input->cmd[i] = ft_itoa(g_var);
        }
        i++;
    }
    int pid = fork();
    if (!pid)
    {
        if (execve("/bin/echo", input->cmd, env) == -1)
        {
            printf("minishell");
        }
    }
    else
        wait(NULL);
    g_var = 0;
}