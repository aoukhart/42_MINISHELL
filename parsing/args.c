/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:25 by ybachaki          #+#    #+#             */
/*   Updated: 2022/10/26 21:32:05 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

void	arg(t_progres *progree, t_input *data)
{
	char	*c;
	char	*arg;

	c = ft_calloc(2, 1);
	arg = NULL;
	if (!c)
		return ;
	while (progree->input[progree->i] && progree->input[progree->i] != '|'
	&& progree->input[progree->i] != '<'
		&& progree->input[progree->i] != '>')
	{
		while (progree->input[progree->i] && progree->input[progree->i] != '|'
		&& progree->input[progree->i] != '<'
		&& progree->input[progree->i] != '>'
		&& progree->input[progree->i] != ' ')
		{
			if (progree->input[progree->i] == '"' || progree->input[progree->i] == '\'')
			{
				arg = ft_strjoin2(arg, quotes_handler(progree));
				continue;
			}
			if (progree->input[progree->i] == '$' && progree->input[progree->i + 1] != '\0'
				&& progree->input[progree->i + 1] != '|'
				&& progree->input[progree->i + 1] != '<'
				&& progree->input[progree->i + 1] != '>'
				&& progree->input[progree->i + 1] != ' ')
			{
				arg = ft_strjoin2(arg, env_var2(progree));
				continue;
			}
			*c =  progree->input[progree->i];
			arg =  ft_strjoin2(arg, c);
			progree->i++;
		}
		skip_spaces(progree);
		add(data, arg);// problem with free
		arg = NULL;
	}
	free(c);
}
