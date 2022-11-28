/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:25 by ybachaki          #+#    #+#             */
/*   Updated: 2022/11/28 07:23:25 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

void	arg(t_progres *progree, t_input *data)
{
	char	*arg;

	arg = NULL;
	while (progree->input[progree->i] && progree->input[progree->i] != '|'
		&& progree->input[progree->i] != '<'
		&& progree->input[progree->i] != '>')
	{
		skip_spaces(progree);
		arg = word_extract(progree);
		if (arg)
			add(data, arg);
		arg = NULL;
	}
}

int	car_check(char c, int i)
{
	if (i == 0)
	{
		if (c && c != '|' && c != '<' && c != '>' && c != ' ')
			return (1);
	}
	else if (i == 1)
	{
		if (c == '"' || c == '\'')
			return (1);
	}
	return (0);
}

char	*word_extract(t_progres *progree)
{
	char	c;
	char	*word;

	word = NULL;
	while (car_check(progree->input[progree->i], 0))
	{
		if (car_check(progree->input[progree->i], 1))
		{
			word = ft_strjoin1(word, quotes_handler(progree));
			continue ;
		}
		if (progree->input[progree->i] == '$'
			&& car_check(progree->input[progree->i + 1], 0))
		{
			word = ft_strjoin1(word, env_3(progree));// srtjoin1 leaks
			continue ;
		}
		c = progree->input[progree->i];
		word = car_join(word, c);
		progree->i++;
	}
	return (word);
}
// skip spaces ???
