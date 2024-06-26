/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:18 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/10 05:35:24 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

void	redirection_handler(t_progres *progree, t_input *data)
{
	t_redirect	*tmp;

	data->redirrections = malloc(sizeof(t_redirect));
	if (!data->redirrections)
		return ;
	init_struct2(data->redirrections);
	tmp = data->redirrections;
	redirect(progree, tmp);
	skip_spaces(progree);
	while (progree->input[progree->i] && progree->input[progree->i] != '|')
	{
		skip_spaces(progree);
		if (progree->input[progree->i] == '>'
			|| progree->input[progree->i] == '<')
		{
			tmp->next = malloc(sizeof(t_redirect));
			if (!tmp->next)
				return ;
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

void	ft_open(t_progres *progree, t_redirect *tmp, int i)
{
	char	*file_name;

	skip_spaces(progree);
	if (i == 2 && tmp->type == '<')
	{
		tmp->delimiter = word_extract(progree, 1);
		return ;
	}
	else
	{
		file_name = word_extract(progree, 0);
		if (i == 2 && tmp->type == '>')
				tmp->fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (tmp->type == '>')
				tmp->fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		else
			tmp->fd = open(file_name, O_RDWR, 0777);
		free(file_name);
	}
}
