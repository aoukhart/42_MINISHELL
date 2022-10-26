/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an_ass <an_ass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/10/25 19:19:08 by an_ass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    echo(t_input *input, char **env)
{
    int i = 1;
    while (input->cmd[i])
    {
        if (input->cmd[i][0] == '$' && input->cmd[i][1] == '?')
        {
            input->cmd[i] = ft_itoa(input->exit_val);
        }
        i++;
    }
    exec(input, env);
    input->exit_val = 0;
}
