/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:09:18 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/16 15:59:34 by aoukhart         ###   ########.fr       */
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
	redirect(progree, tmp, data);
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
			redirect(progree, tmp, data);
		}
		skip_spaces(progree);
		arg(progree, data);
	}
}

void	redirect(t_progres *progree, t_redirect *tmp, t_input *input)
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
	ft_open(progree, tmp, i, input);
}

int	check(t_progres *progree)
{
	t_progres	*tmp;
	char		*str;

	if (car_check(progree->input[progree->i + 1], 0))
	{
		tmp = malloc(sizeof(t_progres));
		tmp->envp = progree->envp;
		tmp->i = progree->i;
		tmp->input = progree->input;
		str = env_3(tmp);
		if (ft_len(ft_split(str, ' ')) > 1)
		{
			progree->i = tmp->i;
			return (1);
		}
	}
	return (0);
}

void	ft_open(t_progres *progree, t_redirect *tmp, int i, t_input *input)
{
	char	*file_name;

	skip_spaces(progree);
	if (i == 2 && tmp->type == '<')
	{
		tmp->delimiter = word_extract(progree, 1, input);
		return ;
	}
	else
	{
		if (progree->input[progree->i] == '$'
			&& check(progree))
		{
			tmp->fd = -2;
			return ;
		}
		file_name = word_extract(progree, 0, input);
		if (i == 2 && tmp->type == '>' && file_name)
			tmp->fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (tmp->type == '>' && file_name)
			tmp->fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
		else if (file_name)
			tmp->fd = open(file_name, O_RDWR, 0777);
		free(file_name);
	}
}
