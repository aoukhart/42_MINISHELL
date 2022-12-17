/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:02:40 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/17 02:02:04 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

size_t	length(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		i++;
	}
	return (i);
}

void	unset_1(char *cmd, t_progres *progress, int len)
{
	int		checker;
	char	**env1;
	int		i;
	int		j;

	checker = check_dup_env(cmd, progress->envp);
	if (checker != -1 && (length(progress->envp[checker]) == length(cmd)))
	{
		env1 = ft_calloc(len, sizeof(char *));
		i = 0;
		j = 0;
		while (i < len)
		{
			if (i == checker)
			{
				free(progress->envp[j]);
				j++;
			}
			env1[i] = progress->envp[j];
			i++;
			j++;
		}
		free(progress->envp);
		progress->envp = env1;
	}
}

void	unset(t_input *input, t_progres *progress)
{
	int	i;
	int	len;

	i = 0;
	if (input->cmd[1])
	{
		while (input->cmd[++i])
		{
			if (export_n_unset_check(input->cmd[i]))
			{
				len = 0;
				while (progress->envp[len])
					len++;
				unset_1(input->cmd[i], progress, len);
			}
		}
	}
	g_var = 0;
}
