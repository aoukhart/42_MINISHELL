/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:12:25 by ybachaki          #+#    #+#             */
/*   Updated: 2022/11/28 09:21:02 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

int	ft_len(char **tab)
{
	int	i;

	i = 0;
	while (*(tab + i))
		i++;
	return (i);
}

void	add(t_input *data, char *str)
{
	int		len;
	char	**new;
	int		i;

	new = NULL;
	i = 0;
	if (!data->cmd)
	{
		data->cmd = ft_calloc(2, sizeof(char *));
		*(data->cmd) = str;
	}
	else
	{
		len = ft_len(data->cmd);
		new = ft_calloc(len + 2, sizeof(char *));
		while (*(data->cmd + i))
		{
			*(new + i) = *(data->cmd + i);
			i++;
		}
		*(new + i) = str;
		free(data->cmd);
		data->cmd = new;
	}
}

void	skip_spaces(t_progres *progree)
{
	while (progree->input[progree->i] && progree->input[progree->i] == ' ')
		progree->i++;
}

char	*car_join(char *s1, char c)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	res = ft_calloc(ft_strlen(s1) + 2, 1);
	if (!res || c == '\0' || !s1) // leaks !! free res
		return (s1);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	free(s1);
	return (res);
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
		while(data->cmd[i])
		{
			free(data->cmd[i]);
			i++;
		}
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

	while(data->redirrections)
	{
		if (data->redirrections->delimiter)
			free(data->redirrections->delimiter);
		temp1 = data->redirrections->next;
		free (data->redirrections);
		data->redirrections = temp1;
	}
}