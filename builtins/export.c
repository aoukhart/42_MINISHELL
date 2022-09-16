#include "../minishell.h"

void    printf_export(char *env)
{
    int i = 0;
    printf("declare -x ");
    if (ft_strchr(env, '='))
    {
        while (env[i]!= '=')
            printf("%c", env[i++]);
        printf("=\"");
        i++;
        printf("%s\"\n", (env + i));
    }
    else
        printf("%s\n", env);
}

int check_dup_env(char *cmd, char **env)
{
    int i = 0;
    if (cmd == NULL)
        return 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], cmd, length(cmd)))
            return (i);
        else
            i++;
    }
    return 0;
}

void    export_1(char *cmd, char **env, int len)
{
    char **env1;
    int i;
    int x;

    i = 0;
    if ((x = check_dup_env(cmd, env)) && ft_strchr(cmd, '=') 
        && (length(cmd) == length(env[x])))
            env[x] = ft_strdup(cmd);
    else if (!check_dup_env(cmd, env))
    {
        env1 = malloc(sizeof(char*) * (len + 2));
        env1[len + 1] = NULL;
        env1[len] = ft_strdup(cmd);
        i = -1;
        while (++i < len)
            env1[i] = ft_strdup(env[i]);
        i = -1;
        while (env1[++i])
            env[i] = ft_strdup(env1[i]);
        env[i] = NULL;
        ft_free(env1);
    }
}

int export_check(char *cmd)
{
    int  i = 1;
    if (cmd[0] != '_' && !ft_isalpha(cmd[0]))
    {
        printf("1apaah[%c]\n", cmd[0]);
        return (0);
    }
    while (cmd[i])
    {
        if (cmd[i] != '_' && !ft_isalnum(cmd[i]))
        {
            printf("2apaah[%c]\n", cmd[i]);
            return (0);
        }
        i++;
    }
    return (1);
}

void export(char **cmd, char **env)
{
    int i;
    int len;

    if (cmd[1])
    {
        i = 1;
        while (cmd[i])
        {
            if (export_check(cmd[i]) == 1)
            {
                len = 0;
                while (env[len])
                    len++;
                export_1(cmd[i], env, len);
            }
            i++;
        }        
    }
    else
    {
        i = -1;
        while (env[++i])
            printf_export(env[i]);
    }
}
