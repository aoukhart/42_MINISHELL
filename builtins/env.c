/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:34:18 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/12 10:12:38 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void    my_env(t_input *input, char **env)
{
    int i;
    (void)input;
    i = -1;
    if (!env)
        printf("salam\n");
    while (env[++i])
    {
        if (ft_strchr(env[i], '='))
            printf("%s\n",env[i]);
    }
    g_var = 0;
}
