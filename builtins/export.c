/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:55:04 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/15 05:42:52 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	printf_export(char *env)
{
	int	i;

	i = 0;
	printf("declare -x ");
	if (ft_strchr(env, '='))
	{
		while (env[i] != '=')
			printf("%c", env[i++]);
		printf("=\"");
		i++;
		printf("%s\"\n", (env + i));
	}
	else
		printf("%s\n", env);
}

void	export_algo(char *cmd, t_progres *progress, int len)
{
	int		i;
	char	**env1;

	env1 = malloc(sizeof (char *) * (len + 2));
	env1[len + 1] = NULL;
	env1[len] = ft_strdup(cmd);
	i = -1;
	while (++i < len)
		env1[i] = progress->envp[i];
	free(progress->envp);
	progress->envp = env1;
}

void	export_1(char *cmd, t_progres *progress, int len)
{
	int	dupl;

	dupl = check_dup_env(cmd, progress->envp);
	if (dupl != -1 && !ft_strchr(cmd, '=')
		&& length(progress->envp[dupl]) == length(cmd))
		return ;
	if (dupl != -1 && ft_strchr(cmd, '=')
		&& (length(cmd) == length(progress->envp[dupl])))
		progress->envp[dupl] = ft_strdup(cmd);
	else
		export_algo(cmd, progress, len);
}

int	export_n_unset_check(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[0] != '_' && !ft_isalpha(cmd[0]))
		return (export_error());
	while (i < (int)length(cmd))
	{
		if (cmd[i] != '_' && !ft_isalnum(cmd[i]))
			return (export_error());
		i++;
	}
	if (ft_strncmp(cmd, " ", 2) == 0)
		return (export_error());
	return (1);
}

void	export(t_input *input, t_progres *progress)
{
	int	i;
	int	len;

	if (progress->envp && input->cmd[1])
	{
		i = 0;
		while (input->cmd[++i])
		{
			if (export_n_unset_check(input->cmd[i]))
			{
				printf("qweqweqwe\n");
				len = -1;
				while (progress->envp[++len])
					;
				export_1(input->cmd[i], progress, len);
			}
		}
	}
	else
	{
		i = -1;
		while (progress->envp[++i])
			printf_export(progress->envp[i]);
	}
}
