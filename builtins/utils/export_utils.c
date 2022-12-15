/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:36:24 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/15 06:04:15 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

int	export_error(void)
{
	ft_putstr_fd("Minishell: not a valid identifier\n", 2);
	g_var = 1;
	return (0);
}

int	check_dup_env(char *cmd, char **env)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (0);
	while (env[i])
	{
		if (!ft_strncmp(env[i], cmd, length(env[i]))
			&& (length(cmd) == length(env[i])))
			return (i);
		else
			i++;
	}
	return (-1);
}