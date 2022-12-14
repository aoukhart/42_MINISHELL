/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:02:40 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/14 07:15:47 by ybachaki         ###   ########.fr       */
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
    return i;
}

void unset_1(char *cmd, t_progres *progress, int len)
{
    int checker;
    char **env1;
    int i;
    int j;

    checker = 0;
    checker = check_dup_env(cmd, progress->envp);
    printf("%d\n", checker);
    if (checker && (length(progress->envp[checker]) == length(cmd)))
    {
        env1 = ft_calloc(len , sizeof(char *));
        i = 0;
        j = 0;
        while (i < len)
        {
            if (i == checker)
            {
                free(progress->envp[j]);
                j++;
            }
            env1[i] = progress->envp[j];
            i++;
            j++;
        }
        printf("<<%s\n", progress->envp[i]);
        free(progress->envp);
        progress->envp = env1;
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
                unset_1(input->cmd[i], progress, len);
            }
            i++;
        }
    }
    g_var = 0;
}