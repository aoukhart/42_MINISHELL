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
        // while (env[i][j])
        i++;
        printf("%s\"\n", (env + i));
    }
    else
        printf("%s\n", env);
}

int check_dup_env(char *cmd, char **env)
{
    int i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], cmd, ft_strlen(cmd)) && (ft_strlen(cmd) == length(env[i])))
            return (i);
        else
            i++;
    }
    return 0;
}

int check_dup_env_2(char *cmd, char **env)
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

void    export(char **cmd, char **env)
{
    int len;
    char **env1;
    int i;

    i = 0;
    len = 0;
    if (check_dup_env_2(cmd[1], env) && ft_strchr(cmd[1], '=') && (length(cmd[1]) == length(env[check_dup_env_2(cmd[1], env)])))
        env[check_dup_env_2(cmd[1], env)] = ft_strdup(cmd[1]);
    else if (cmd[1] && !check_dup_env(cmd[1], env))
    {
        while (env[len])
            len++;
        env1 = malloc(sizeof(char*) * (len + 2));
        env1[len + 1] = NULL;
        env1[len] = ft_strdup(cmd[1]);
        i = -1;
        while (++i < len)
            env1[i] = ft_strdup(env[i]);
        i = -1;
        while (env1[++i])
            env[i] = ft_strdup(env1[i]);

        env[i] = NULL;
        ft_free(env1);
    }
    else if (cmd[1] == NULL)
    {
        i = -1;
        while (env[++i])
            printf_export(env[i]);
    }
}