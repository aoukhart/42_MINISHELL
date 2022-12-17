/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:58:00 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/16 19:18:37 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	get_in(t_input *tmp, int fd_in)
{
	t_redirect	*tmp1;
	int			fd;
	int			flag;

	tmp1 = tmp->redirrections;
	while (tmp1)
	{
		if (tmp1->type == '<' && !tmp1->delimiter)
			fd_in = tmp1->fd;
		else if (tmp1->type == '<' && tmp1->delimiter)
		{
			flag = 1;
			fd = open("minishell_0", O_RDWR);
			if (fd != -1)
				fd_in = fd;
		}
		tmp1 = tmp1->next;
	}
	if (flag)
		unlink ("minishell_0");
	return (fd_in);
}

int	get_out(t_input *tmp, int fd_out)
{
	t_redirect	*tmp1;

	tmp1 = tmp->redirrections;
	fd_out = 1;
	while (tmp1)
	{
		if (tmp1->type == '>' && !tmp1->delimiter)
			fd_out = tmp1->fd;
		tmp1 = tmp1->next;
	}
	return (fd_out);
}

int	get_in_v2(t_input *tmp, int fd_in, int index)
{
	t_redirect	*tmp1;
	int			fd;

	tmp1 = tmp->redirrections;
	while (tmp1)
	{
		if (tmp1->type == '<' && !tmp1->delimiter)
			fd_in = tmp1->fd;
		else if (tmp1->type == '<' && tmp1->delimiter)
		{
			fd = open(ft_strjoin("minishell_", ft_itoa(index)), O_RDWR);
			if (fd != -1)
				fd_in = fd;
		}
		tmp1 = tmp1->next;
	}
	if (fd)
		unlink(ft_strjoin("minishell_", ft_itoa(index)));
	return (fd_in);
}

void	dup_in_out(int in, int out)
{
	if (in)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	restore_fd(int in, int out, int new_in, int new_out)
{
	if (in)
	{
		dup2(new_in, STDIN_FILENO);
		close(new_in);
	}
	if (out != 1)
	{
		dup2(new_out, STDOUT_FILENO);
		close(new_out);
	}
}
