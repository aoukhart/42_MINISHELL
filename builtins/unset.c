/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:02:40 by aoukhart          #+#    #+#             */
/*   Updated: 2022/09/11 21:25:11 by aoukhart         ###   ########.fr       */
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
    // printf("%zu\n", i);
    return i;
}

void unset(char **cmd, char **env)
{
    int len;
    int checker;
    char **env1;
    int i;
    int j = 0;

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

                checker = i;
                break;
            }
            i++;
        }
        i = 0;
        while (env[i])
        {
            printf("--%s--\n", env[i]);
            i++;
        }
        if (checker)
        {
            env1 = malloc(sizeof(char*) * (len));
            i = 0;
            j = 0;
            while (i < len)
            {
                if (i >= checker)
                {
                    j++;
                    env1[i] = ft_strdup(env[j]);
                }
                else
                {
                    env1[i] = ft_strdup(env[j]);
                    j++;
                }
                i++;
            }
            env1[len - 1] = NULL;
            i = -1;
            while (env1[++i])
                printf("[%s]\n", env1[i]);
        }
        i = -1;
        env = malloc(sizeof(char*) * (len));
        //    printf("--->%s(%d)\n", env1[i], i);
        env[len - 1] = NULL;
        ft_free(env1);
    }
    else
    {
        i = 0;
        while (env[i])
            printf("%s\n", env[i++]);
    } 
}
