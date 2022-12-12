/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:12:01 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/10 05:47:58 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

char	*quotes_handler(t_progres *progree, int i)
{
	if (progree->input[progree->i] == '"')
		return (d_quotes_handler(progree, i));
	return (s_quotes_handler(progree));
}

char	*s_quotes_handler(t_progres *progree)
{
	char	car;
	char	*arg;
	char	c;

	arg = NULL;
	car = progree->input[progree->i];
	progree->i++;
	while (progree->input[progree->i] && progree->input[progree->i] != car)
	{
		c = progree->input[progree->i];
		arg = car_join(arg, c);
		progree->i++;
	}
	if (progree->input[progree->i])
		progree->i++;
	return (arg);
}

char	*d_quotes_handler(t_progres *progree, int i)
{
	char	car;
	char	*arg;
	char	c;

	arg = NULL;
	car = progree->input[progree->i];
	progree->i++;
	while (progree->input[progree->i] && progree->input[progree->i] != car)
	{
		if (progree->input[progree->i] == '$'
			&& progree->input[progree->i + 1] != '\0'
			&& progree->input[progree->i + 1] != car
			&& i == 0)
		{
			arg = ft_strjoin1(arg, env_3(progree));
			continue ;
		}
		c = progree->input[progree->i];
		arg = car_join(arg, c);
		progree->i++;
	}
	if (progree->input[progree->i])
		progree->i++;
	return (arg);
}

char	*heredoc(t_progres *progree)
{
	char	*arg;
	char	c;

	arg = NULL;
	if (progree->input && progree->input[0] == '\0')
		return ("\0");
	while (progree->input && progree->input[progree->i])
	{
		if (progree->input[progree->i] == '$'
			&& progree->input[progree->i + 1] != '\0')
		{
			arg = ft_strjoin1(arg, env_3(progree));
			continue ;
		}
		c = progree->input[progree->i];
		arg = car_join(arg, c);
		progree->i++;
	}
	return (arg);
}
