/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:39:15 by aoukhart          #+#    #+#             */
/*   Updated: 2022/12/13 12:08:50 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	check_n(char *str)
{
	int	y;

	y = 1;
	while(str && str[y] && str[y] == 'n')
		y++;
	if (y == (int)ft_strlen(str))
		return (1);
	else
		return (0);
}

void	echo_appah(t_input	*input)
{
	int	y;
	int	a;
    int free;
	char	**new_cmd;

	y = 1;
	a = 2;
	while(input->cmd && input->cmd[y] && input->cmd[y][0] == '-'
		&& check_n(input->cmd[y]))
		y++;
	if (y > 1)
	{
        free = y;
		new_cmd = ft_calloc(ft_len(input->cmd) - y + 3, sizeof(char *));
		new_cmd[0] = input->cmd[0];
		new_cmd[1] = ft_strdup("-n");
		while(input->cmd[a])
			new_cmd[a++] = input->cmd[y++];
        free_dptr(input, free);
		input->cmd = new_cmd;
	}
}

void    echo(t_input *input, t_progres *progress)
{
    int i = 1;

    echo_appah(input);
    
    while (input->cmd[i])
    {
        if (input->cmd[i][0] == '$' && input->cmd[i][1] == '?')
        {
            input->cmd[i] = ft_itoa(g_var);
        }
        i++;
    }
    int pid = fork();
    if (!pid)
    {
        if (execve("/bin/echo", input->cmd, progress->envp) == -1)
        {
            perror("minishell");
			exit(1);
        }
    }
    else
        wait(NULL);
    g_var = 0;
}
