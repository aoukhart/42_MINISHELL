/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:25 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/14 16:37:50 by aoukhart         ###   ########.fr       */
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
		arg = word_extract(progree, 0, data);
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

char	*split_after_expand(char *value, char *word, t_input *input)
{
	char	**res;
	int		lent;
	int		i;

	i = 1;
	if (!value)
		return (word);
	res = ft_split(value, ' ');
	free(value);
	lent = ft_len(res);
	word = ft_strjoin1(word, res[0]);
	if (lent > 1)
	{
		add(input, word);
		while (i < lent - 1)
		{
			add(input, res[i]);
			i++;
		}
		free(res);
		return (res[i]);
	}
	free(res);
	return (word);
}

char	*word_extract(t_progres *progree, int i, t_input *input)
{
	char	c;
	char	*word;

	word = NULL;
	while (car_check(progree->input[progree->i], 0))
	{
		if (car_check(progree->input[progree->i], 1))
		{
			word = ft_strjoin1(word, quotes_handler(progree, i));
			continue ;
		}
		if (progree->input[progree->i] == '$'
			&& car_check(progree->input[progree->i + 1], 0)
			&& i == 0)
		{
			/*word = ft_strjoin1(word, env_3(progree));*/
			word = split_after_expand(env_3(progree), word, input);
			continue ;
		}
		c = progree->input[progree->i];
		word = car_join(word, c);
		progree->i++;
	}
	return (word);
}
