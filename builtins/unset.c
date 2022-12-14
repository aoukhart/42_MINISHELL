/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:02:40 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/13 15:29:49 by aoukhart         ###   ########.fr       */
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
    printf("%d\n", checker);
    if (checker && (length(env[checker]) == length(cmd)))
    {
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
            printf("<<%s\n", env[i]);
            i++;
        }
        i = -1;
        while (env1[++i])
            env[i] = ft_strdup(env1[i]);
        env[i] = NULL;
        ft_free(env1);
    }
}

int unset_check(char *cmd)
{
    int i = 0;
    while (cmd[i])
    {
        if (ft_strchr(&cmd[i], '='))
        {
            ft_putstr_fd("Minishell: not a valid identifier\n", 2);
            g_var = 1;
            return (0);
        }
        i++;
    }
    return 1;
}

void    unset(t_input *input, t_progres *progress)
{
    int  i = 1;
    int len;
    if (input->cmd[1])
    {
        while (input->cmd[i])
        {
            if (unset_check(input->cmd[i]))
            {
                len = 0;
                while (progress->envp[len])
                    len++;
                unset_1(input->cmd[i], progress->envp, len);
            }
            i++;
        }
    }
    g_var = 0;
}