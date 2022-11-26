/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:18:03 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/25 22:52:47 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

char	*env_var(t_progres *progree)
{
	int		i;
	char	*var;
	char	*c;

	i = 0;
	var = NULL;
	c = ft_calloc(2, 1);
	if (!c)
		return (0);
	progree->i++;
	if (progree->input[progree->i] == '?')
	{
		progree->i++;
		return ("$?");
	}
	while (progree->input[progree->i] && progree->input[progree->i] != ' '
		&& progree->input[progree->i] != '"')
	{
		*c = progree->input[progree->i];
		var = ft_strjoin1(var, c);
		progree->i++;
	}
	return (ft_chr(progree->envp, var));
}

char	*env_var2(t_progres *progree)
{
	char	*var;
	char	c;

	var = NULL;
	progree->i++;
	if (progree->input[progree->i] == '?')
	{
		progree->i++;
		return ("$?");
	}
	while (car_check(progree->input[progree->i], 0))
	{
		c = progree->input[progree->i];
		var = car_join(var, c);
		progree->i++;
	}
	return (ft_chr(progree->envp, var));
}

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
				return (*(env + i) + j + 1);
			}
		}
		i++;
	}
	free(variabel);
	return (NULL);
}
