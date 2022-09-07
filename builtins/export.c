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
        {
            printf("-->%s\n", env[i]);
            return 1;
        }
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
    if (cmd[1] && !check_dup_env(cmd[1], env))
    {
        while (env[len])
            len++;
        if (!ft_strncmp(env[i], cmd[1], length(env[i])))
        {
            env1 = malloc(sizeof(char*) * (len + 1));
            env1[len] = NULL;
        }
        else
        {
            env1 = malloc(sizeof(char*) * (len + 2));
            env1[len + 1] = NULL;
            // if (len == 30)
                env1[len] = ft_strdup(cmd[1]);
        }
        i = -1;
        while (++i < len)
        {
            if (!ft_strncmp(env[i], cmd[1], length(env[i])))
            {
                env1[i] = ft_strdup(cmd[1]);
                i++;    
            }
            else
                env1[i] = ft_strdup(env[i]);
        }
        i = -1;
        while (env1[++i])
            env[i] = ft_strdup(env1[i]);
        env[i] = NULL;
        // ft_free(env1);
    }
    else
    {
        i = -1;
        while (env[++i])
        {
            printf_export(env[i]);
        }
    }
}