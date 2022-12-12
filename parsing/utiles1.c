/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:05:48 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/01 14:06:32 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

void	ft_free1(t_progres *progree, t_input *data)
{
	int			i;
	t_input		*temp;

	free(progree->input);
	free(progree);
	while (data)
	{
		i = 0;
		while (data->cmd && data->cmd[i])
		{
			free(data->cmd[i]);
			i++;
		}
		if (data->cmd)
			free(data->cmd);
		ft_free2(data);
		temp = data->next;
		free(data);
		data = temp;
	}
}

void	ft_free2(t_input *data)
{
	t_redirect	*temp1;

	while (data->redirrections)
	{
		if (data->redirrections->delimiter)
			free(data->redirrections->delimiter);
		temp1 = data->redirrections->next;
		free (data->redirrections);
		data->redirrections = temp1;
	}
}
