/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:18 by ybachaki          #+#    #+#             */
/*   Updated: 2022/10/26 21:32:05 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

void	redirection_handler(t_progres *progree, t_input *data)
{
	t_redirect	*tmp;

	data->redirrections = malloc(sizeof(t_redirect));
	if (!data->redirrections)
		return;
	init_struct2(data->redirrections);
	tmp = data->redirrections;
	redirect(progree, tmp);
	skip_spaces(progree);
	while( progree->input[progree->i] && progree->input[progree->i] != '|')
		{
			skip_spaces(progree);
			if (progree->input[progree->i] == '>' || progree->input[progree->i] == '<')
			{
				tmp->next = malloc(sizeof(t_redirect));
				if (!tmp->next)
					return;
				tmp = tmp->next;
				init_struct2(tmp);
				redirect(progree, tmp);
			}
			skip_spaces(progree);
			arg(progree, data);
		}
}

void	redirect(t_progres *progree, t_redirect *tmp)
{
	int	i;

	i = 1;
	
	if (progree->input[progree->i] == '>')
	{
		tmp->type = '>';
		if (progree->input[progree->i + 1] == '>')
			i = 2;
	}
	else if (progree->input[progree->i] == '<')
	{
		tmp->type = '<';
		if (progree->input[progree->i + 1] == '<')
			i = 2;
	}
	if (i == 2)
		progree->i++;
	progree->i++;
	ft_open(progree, tmp, i);
}

char	*word_extract(t_progres *progree)
{
	char	*c;
	char	*word;

	c = ft_calloc(2, 1);
	word = NULL;
	if (!c)
		return (NULL);
	while (progree->input[progree->i] && progree->input[progree->i] != '|'
		&& progree->input[progree->i] != '<'
		&& progree->input[progree->i] != '>'
		&& progree->input[progree->i] != ' ')
	{
        if (progree->input[progree->i] == '"' || progree->input[progree->i] == '\'')
			{
			    word = ft_strjoin2(word, quotes_handler(progree));
				continue;
			}
		if (progree->input[progree->i] == '$' && progree->input[progree->i + 1] != '\0'
			&& progree->input[progree->i + 1] != '|'
			&& progree->input[progree->i + 1] != '<'
			&& progree->input[progree->i + 1] != '>'
			&& progree->input[progree->i + 1] != ' ')
		{
			word = ft_strjoin2(word, env_var2(progree));
			continue;
		}
		*c = progree->input[progree->i];
		word = ft_strjoin2(word, c);
		progree->i++;
	}
	return (word);
}

void	ft_open(t_progres *progree, t_redirect *tmp, int	i)
{
	char	*file_name;

	skip_spaces(progree);
	file_name = word_extract(progree);
	if (i == 2)
		tmp->fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND);
	else
		if(tmp->type == '>')
			tmp->fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		tmp->fd = open(file_name, O_RDONLY, 0644);
}
