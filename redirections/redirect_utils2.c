/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:19:34 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/15 00:12:04 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void dup_in_out(int in, int out)
{
	if (in)
	{
		dup2(in, STDIN_FILENO);
		// close(in);
	}
	if (out != 1)
	{
		dup2(out, STDOUT_FILENO);
		// close(out);
	}
}

void restore_fd(int in, int out, int new_in, int new_out)
{
	if (in)
	{
		dup2(new_in, STDIN_FILENO);
		// close(new_in);
	}
	if (out != 1)
	{
		dup2(new_out, STDOUT_FILENO);
		// close(new_out);
	}
}
