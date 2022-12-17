/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:05:48 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/17 00:06:21 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../INCLUDE/minishell.h"

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

void	free_dptr(t_input *input, int j)
{
	int	i;

	i = 1;
	while (i < j)
	{
		free(input->cmd[i]);
		i++;
	}
	free(input->cmd);
}

void	check_error_main(int in, int out)
{
	if (in == -1 || out == -1)
	{
		perror("minishell");
		g_var = 1;
		return ;
	}	
	if (in == -2 || out == -2)
	{
		ft_putstr_fd("minishell: ambigious redirect\n", 2);
		g_var = 1;
		return ;
	}
}
