/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an_ass <an_ass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:12:25 by ybachaki          #+#    #+#             */
/*   Updated: 2022/10/24 15:53:33 by an_ass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_len(char **tab)
{
	int i;

	i = 0;
	while(*(tab + i))
		i++;
	return (i);
}

void	add(t_input *data, char *str)
{
	int		len;
	char	**new;
	int		i;
	
	if(!str)
		return;
	new = NULL;
	i = 0;
	if (!data->cmd)
	{
		data->cmd = ft_calloc(2, sizeof(char *));
		*(data->cmd) = str;
	}
	else{
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
	while( progree->input[progree->i] && progree->input[progree->i] == ' ')
		progree->i++;
}