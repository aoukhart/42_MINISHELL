#include "../INCLUDE/minishell.h"

void	change_old_pwd(char *old_pwd, char **env)
{
	int i = 0;
			
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			env[i] = ft_strjoin("OLDPWD=", old_pwd);
		i++;
	}
}

void	change_pwd(char *pwd, char **env)
{
	int i = 0;
	while (env[i])
	{
		if(ft_strncmp(env[i], "PWD=", 4) == 0)
			env[i] = ft_strjoin("PWD=", pwd);
		i++;
	}
}

void    cd(t_input *input, char **env)
{
	char *old_p;
	char *cwd;
	char *home;
	old_p = getcwd(NULL, 1000);
	change_old_pwd(old_p, env);
	if (input->cmd[2])
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		g_var = 1;
		return;
	}
		
	else if(printf("azezaea\n") && !ft_strncmp(input->cmd[1], "-", 2))
	{
		chdir(ft_chr(env, "OLDPWD"));
		pwd(input, env);
	}
	else if (input->cmd[1] == NULL || !ft_strncmp(input->cmd[1] ,"~", 2))
	{
		if (ft_chr(env, "HOME"))
		{
			home = ft_chr(env, "HOME");
			chdir(home);
		}
		else
		{
			ft_putstr_fd("minishell: HOME not set\n", 2);
			g_var = 1;
		}
	}
	else if (chdir(input->cmd[1]))
	{
		perror("minishell");
		g_var = 1;
	}
	cwd = getcwd(NULL, 1000);
	change_pwd(cwd, env);
}
 