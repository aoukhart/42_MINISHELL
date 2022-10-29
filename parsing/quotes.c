/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:12:01 by ybachaki          #+#    #+#             */
/*   Updated: 2022/10/26 21:32:05 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

char	*quotes_handler(t_progres *progree)
{
    if(progree->input[progree->i] == '"')
        return (d_quotes_handler(progree));
    return (s_quotes_handler(progree));
}

char	*s_quotes_handler(t_progres *progree)
{
	char	car;
	char	*arg;
	char	*c;

	c = ft_calloc(2, 1);
	if(!c)
		return (0);
	arg = NULL;
	car = progree->input[progree->i];
	progree->i++;
	while (progree->input[progree->i] && progree->input[progree->i] != car)
	{
		*c =  progree->input[progree->i];
		arg =  ft_strjoin2(arg, c);
		progree->i++;
	}
	if(progree->input[progree->i])
		progree->i++;
	return (arg);
}

char	*d_quotes_handler(t_progres *progree)
{
	char	car;
	char	*arg;
	char	*c;

	c = ft_calloc(2, 1);
	if(!c)
		return (0);
	arg = NULL;
	car = progree->input[progree->i];
	progree->i++;
	while (progree->input[progree->i] && progree->input[progree->i] != car)
	{
		if (progree->input[progree->i] == '$' && progree->input[progree->i + 1] != '\0'
		&& progree->input[progree->i + 1] != car)
			{
				arg = ft_strjoin2(arg, env_var(progree));
				continue;
			}
		*c =  progree->input[progree->i];
		arg =  ft_strjoin2(arg, c);
		progree->i++;
	}
	if(progree->input[progree->i])
		progree->i++;
	return (arg);
}
