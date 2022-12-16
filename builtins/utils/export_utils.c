/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:36:24 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/16 17:50:02 by aoukhart         ###   ########.fr       */
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

char	**add_after_split(char **src, char **dest)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 1;
	res = ft_calloc(ft_len(src) + ft_len(dest), sizeof(char *));
	while (dest[i])
	{
		res[i] = dest[i];
		i++;
	}
	while (src[j])
	{
		res[i] = src[j];
		j++;
		i++;
	}
	free(dest);
	free(src[0]);
	free(src);
	return (res);
}
