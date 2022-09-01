#include "../minishell.h"

void	change_old_pwd(char *old_pwd, char **env)
{
	int i = 0;
			
	//printf("<%s>\n", ft_strjoin("OLDPWD=", old_pwd));
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

void    cd(char **cmd, char **env)
{
	char *old_p;
	char *pwd;

	old_p = getcwd(NULL, 1000);
	change_old_pwd(old_p, env);
	chdir(cmd[1]);
	pwd = getcwd(NULL, 1000);
	change_pwd(pwd, env);
}
