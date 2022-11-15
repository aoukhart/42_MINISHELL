/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:02:40 by aoukhart          #+#    #+#             */
/*   Updated: 2022/11/03 18:13:37 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

size_t length(char *s)
{
    size_t i = 0;
    while (s[i] && s[i] != '=')
    {
        i++;
    }
    // printf("%zu\n", i);
    return i;
}

void unset_1(char *cmd, char **env, int len)
{
    int checker;
    char **env1;
    int i;
    int j;

    checker = 0;
    env1 = NULL;
    checker = check_dup_env(cmd, env);
    if (checker && (length(env[checker]) == length(cmd)))
    {
        printf("%d\n",checker);
        env1 = malloc(sizeof(char*) * (len));
        i = 0;
        j = 0;
        while (i < len)
        {
            if (i >= checker && i != (len - 1))
            {
                j++;
                env1[i] = ft_strdup(env[j]);
            }
            else if (i == (len - 1))
                env1[i] = NULL;
            else
                env1[i] = ft_strdup(env[j++]);
            i++;
        }
        i = -1;
        while (env1[++i])
            env[i] = ft_strdup(env1[i]);
        env[i] = NULL;
        ft_free(env1);
    }
}

void    unset(char **cmd, char **env)
{
    int  i = 1;
    int len;
    if (cmd[1])
    {
        while (cmd[i])
        {
            len = 0;
            while (env[len])
                len++;
            unset_1(cmd[i], env, len);
            i++;
        }
    }
    g_var = 0;
}