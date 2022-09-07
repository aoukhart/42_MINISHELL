/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:02:40 by aoukhart          #+#    #+#             */
/*   Updated: 2022/09/05 21:19:53 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t length(char *s)
{
    size_t i = 0;
    while (s[i] && s[i] != '=')
    {
        i++;
    }
    return i;
}

void unset(char **cmd, char **env)
{
    int len;
    int checker;
    char **env1;
    int i;

    i = 0;
    len = 0;
    checker = 0;
    env1 = NULL;
    if (cmd[1])
    {
        while (env[len])
            len++;
        printf("LEN IS : %d\n", len);
        while (env[i])
        {
            if (!ft_strncmp(env[i], cmd[1], ft_strlen(cmd[1])) && (ft_strlen(cmd[1]) == length(env[i])))
            {
                printf("{%s:%d}\n", env[i], i);
                checker = 1;
                break;
            }
            i++;
        }
        if (checker == 1)
        {
            env1 = malloc(sizeof(char*) * (len));
            env1[len] = NULL;
            while (i < len)
            {
                if (ft_strncmp(env[i], cmd[1], ft_strlen(cmd[1])))
                    env1[i] = ft_strdup(env[i]);
                i++;
            }
        }
        i = 0;
        
        i = -1;
        while (env1[++i])
           printf("--->%s\n", env1[i]);
        //ft_free(env1);
    }
    else
    {
        i = 0;
        while (env[i])
            printf("%s\n", env[i++]);
    } 
}
