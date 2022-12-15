/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:34:18 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/14 17:40:59 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	my_env(t_input *input, t_progres *progress)
{
	int	i;

	(void)input;
	i = -1;
	if (!progress->envp)
		return ;
	while (progress->envp[++i])
	{
		if (ft_strchr(progress->envp[i], '='))
			printf("%s\n", progress->envp[i]);
	}
	g_var = 0;
}
