/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an_ass <an_ass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/10/12 19:18:34 by an_ass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    echo(char **cmd, char **env)
{
    int i = 1;
    while (cmd[i])
    {
        //if (cmd[i][0] == '$' && cmd[i][1] == '?')
        //{
        //    // g_ret += 127;
        //    //cmd[i] = ft_strdup(ft_itoa(g_value));
        //}
        //else if (check_dup_env(cmd[i] + 1, env) && 
        //    ft_strlen(cmd[i] + 1) == length(env[check_dup_env(cmd[i] + 1, env)]))
        //{
            int j = 0;
            char *tmp = ft_strdup("");
            char *xpand = ft_strdup("");
            int y = 0;
            while (cmd[i][j] && (cmd[i][j] != '$'))
            {
                tmp[y] = cmd[i][j];
                j++;
                y++;
            }
            if (cmd[i][j++] == '$')
            {
                printf("expand to:\n");
                y = 0;
                while(cmd[i][j] && (ft_isalnum(cmd[i][j])) && (cmd[i][j] != '$'))
                {
                    xpand[y] = cmd[i][j];
                    j++;
                    y++;
                }
                xpand[y] = '\0';
            }
            printf("<<%s\n", tmp);
            printf("<<%s----%s\n", xpand, env[check_dup_env(xpand, env)]);
        //    cmd[i] = ft_strdup(env[check_dup_env(cmd[i] + 1, env)] + length(cmd[i]));
        //    
        //}
        //else if (check_dup_env(cmd[i] + 1, env) == 0 && cmd[i][0] == '$')
        //    cmd[i] = ft_strdup("");
        //    
        i++;
    }
    //exec(cmd, env);
}
