/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an_ass <an_ass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:12:11 by ybachaki          #+#    #+#             */
/*   Updated: 2022/10/25 18:20:17 by an_ass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*env_var(t_progres *progree)
{
	char	*var;
	char	*c;

	var = NULL;
	c = ft_calloc(2, 1);
	if (!c)
		return (0);
	progree->i++;
	if (progree->input[progree->i] == '?')
	{
		progree->i++;
		return "$?";
	}
	while(progree->input[progree->i] && progree->input[progree->i] != ' '
	&& progree->input[progree->i] != '"')
	{
		*c = progree->input[progree->i];
		var =ft_strjoin2(var, c);
		progree->i++;
	}
	return (ft_chr(progree->envp, var));
}

char	*env_var2(t_progres *progree)
{
	char	*var;
	char	*c;

	var = NULL;
	c = ft_calloc(2, 1);
	if (!c)
		return (0);
	progree->i++;
	if (progree->input[progree->i] == '?')
	{
		progree->i++;
		return "$?";
	}
	while(progree->input[progree->i] && progree->input[progree->i] != '|'
		&& progree->input[progree->i] != '<'
		&& progree->input[progree->i] != '>'
		&& progree->input[progree->i] != ' ')
	{
		*c = progree->input[progree->i];
		var =ft_strjoin2(var, c);
		progree->i++;
	}
	return (ft_chr(progree->envp, var));
}

char	*ft_chr(char **env, char *variabel)
{
	int	i;
	int	j;

	i = 0;
	while(env[i])
	{
		if (env[i][0] == *variabel)
		{
			j = 0;
			while(env[i][j] && variabel[j] && env[i][j] == variabel[j])
				j++;
			if (env[i][j] == '=' && !variabel[j])
				return (*(env + i) + j + 1);
		}
		i++;
	}
	return (0);
}
