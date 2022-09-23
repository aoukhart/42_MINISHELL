#include "../minishell.h"

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

void    cd(char **cmd, char **env)
{
	char *old_p;
	char *pwd;

	old_p = getcwd(NULL, 1000);
	change_old_pwd(old_p, env);
	if (cmd[1] == NULL || (cmd[1][0] == '~' && !cmd[1][1]))
	{
		printf("<%s>\n", env[check_dup_env("HOME", env)] + length("HOME") + 1);
		chdir(env[check_dup_env("HOME", env)] + length("HOME") + 1);
	}
	if (chdir(cmd[1]))
	{
		write(2, "minishell:", 11);
		printf("%s\n", strerror(2));
	}
	pwd = getcwd(NULL, 1000);
	change_pwd(pwd, env);
}
 