/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:29:12 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/15 23:33:54 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	change_pwds(char *pwd, char *oldpwd, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", pwd);
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
		i++;
	}
	free(pwd);
	free(oldpwd);
}

void	ft_chdir(char *path, char **env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 1000);
	if (chdir(path))
	{
		perror("minishalal");
		g_var = 1;
		return;
	}
	change_pwds(getcwd(NULL, 0), oldpwd, env);
}

void	handle_cd_underscore(t_input *input, t_progres *progress)
{
	char	*oldpwd;

	oldpwd = ft_chr(progress->envp, ft_strdup("OLDPWD"));
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: OLDPWD not set\n", 2);
		g_var = 1;
		return ;
	}
	ft_chdir(oldpwd, progress->envp);
	pwd(input, progress);
	free(oldpwd);
}

void	cd_home(t_progres *progress)
{
	char	*home;

	home = ft_chr(progress->envp, ft_strdup("HOME"));
	if (home)
	{
		ft_chdir(home, progress->envp);
		free(home);
		return ;
	}
	else
	{
		free(home);
		ft_putstr_fd("minishell: HOME not set\n", 2);
		g_var = 1;
	}
}

void	cd(t_input *input, t_progres *progress)
{
	if (input->cmd[1])
	{
		if (input->cmd[2])
		{
			ft_putstr_fd("minishell: too many arguments\n", 2);
			g_var = 1;
			return ;
		}
		else if (!ft_strncmp(input->cmd[1], "-", 2))
			handle_cd_underscore(input, progress);
		else
			ft_chdir(input->cmd[1], progress->envp);
		return ;
	}
	else if (input->cmd[1] == NULL || !ft_strncmp(input->cmd[1], "~", 2))
		cd_home(progress);
}
