/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:35:10 by an4ss             #+#    #+#             */
/*   Updated: 2022/11/22 18:13:47 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void close_all(int fd[2])
{
    if (fd[0] != -1)
        close(fd[0]);
    if (fd[1] != -1)
        close(fd[1]);	
    fd[0] = -1;
	fd[1] = -1;
}

void wait_all(int *pid, int x)
{
    int status;
	int i = 0;
	while (i < x)
	{
		waitpid(pid[i], &status, 0);
        if (WIFEXITED(status))
            g_var = WEXITSTATUS(status);
        else
            g_var = 128 + WTERMSIG(status);
        i++;
	}
}