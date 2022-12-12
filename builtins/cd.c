#include "../INCLUDE/minishell.h"

void	change_pwds(char *pwd, char *oldpwd, char **env)
{
	int i = 0;
	while (env[i])
	{
		if(ft_strncmp(env[i], "PWD=", 4) == 0)
			env[i] = ft_strjoin("PWD=", pwd);
		i++;
	}
	i = 0;		
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
		i++;
	}
}

void	ft_chdir(char *path, char **env)
{
	char *oldpwd = getcwd(NULL, 1000);
	if (chdir(path))
	{
		perror("minishalal");
		g_var = 1;
	}
	change_pwds(getcwd(NULL, 1000), oldpwd, env);
}

void    cd(t_input *input, char **env)
{
	char *home;
	if (input->cmd[1])
	{
		if (input->cmd[2])
		{
			ft_putstr_fd("minishell: too many arguments\n", 2);
			g_var = 1;
			return;
		}
		else if (!ft_strncmp(input->cmd[1], "-", 2))
		{
			char *oldpwd = ft_chr(env, ft_strdup("OLDPWD"));
			if (!oldpwd)
			{
				ft_putstr_fd("minishell: OLDPWD not set\n", 2);
				g_var = 1;
				return;
			}
			ft_chdir(oldpwd, env);
			pwd(input, env);
			return;
		}
		else
		{
			ft_chdir(input->cmd[1], env);
			return;
		}
	}
	else if (input->cmd[1] == NULL || !ft_strncmp(input->cmd[1] ,"~", 2))
	{
		if (ft_chr(env, ft_strdup("HOME")))
		{
			home = ft_chr(env, ft_strdup("HOME"));
			char *oldpwd = getcwd(NULL, 1000);
			chdir(home);
			change_pwds(getcwd(NULL, 1000), oldpwd, env);
			return;
		}
		else
		{
			ft_putstr_fd("minishell: HOME not set\n", 2);
			g_var = 1;
		}
	}
}
 