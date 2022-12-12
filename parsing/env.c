/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:18:03 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/12 08:26:55 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

char	*ft_chr(char **env, char *variabel)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == *variabel)
		{
			j = 0;
			while (env[i][j] && variabel[j] && env[i][j] == variabel[j])
				j++;
			if (env[i][j] == '=' && !variabel[j])
			{
				free(variabel);
				return (ft_strdup(*(env + i) + j + 1));
			}
		}
		i++;
	}
	free(variabel);
	return (NULL);
}

char	*env_3(t_progres *progree)
{
	if (ft_isdigit(progree->input[progree->i + 1]))
	{
		progree->i += 2;
		return (NULL);
	}
	else if (ft_isalpha(progree->input[progree->i + 1])
		|| progree->input[progree->i + 1] == '_')
	{
		return (env_alpha(progree));
	}
	else if (progree->input[progree->i + 1] == '?')
	{
		progree->i += 2;
		return (ft_itoa(g_var));
	}
	else if (progree->input[progree->i + 1] == '$')
	{
		progree->i += 2;
		return (ft_strdup("$$"));
	}
	progree->i++;
	return (NULL);
}

char	*env_alpha(t_progres *progree)
{
	char	*str;

	str = NULL;
	progree->i++;
	while (progree->input[progree->i] != '$'
		&& (ft_isalnum(progree->input[progree->i])
			|| progree->input[progree->i] == '_'))
	{
		str = car_join(str, progree->input[progree->i]);
		progree->i++;
	}
	return (ft_chr(progree->envp, str));
}
