/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/09/16 03:54:38 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    echo(char **cmd, char **env)
{
    int i = 1;
    while (cmd[i])
    {

        if (cmd[i][0] == '$' && cmd[i][1] == '?')
        {
            // g_ret += 127;
            cmd[i] = ft_strdup(ft_itoa(g_ret));
        }
        else if (check_dup_env(cmd[i] + 1, env) && cmd[i][0] == '$' && 
            ft_strlen(cmd[i] + 1) == length(env[check_dup_env(cmd[i] + 1, env)]))
                cmd[i] = ft_strdup(env[check_dup_env(cmd[i] + 1, env)] + length(cmd[i]));
        else if (check_dup_env(cmd[i] + 1, env) == 0 && cmd[i][0] == '$')
            cmd[i] = ft_strdup("");
            
        i++;
    }
    execute(cmd, env);
    g_ret = 0;
}