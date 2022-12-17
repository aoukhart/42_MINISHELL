/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:03 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/17 01:18:05 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDE/minishell.h"

int	g_var;

char	**init_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	if (envp[0] == NULL)
	{
		env = ft_calloc(sizeof (char *), 1);
		return (env);
	}
	while (envp[i++])
		;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}

int	input_checker(t_input *input)
{
	t_input		*temp;
	t_redirect	*temp_r;

	temp = input;
	while (temp)
	{
		temp_r = temp->redirrections;
		if (temp->pipe == 1 && (!temp->next || !temp->cmd) && !temp_r)
			return (1);
		while (temp_r)
		{
			if (temp_r->fd == -3 && temp_r->delimiter == NULL)
				return (1);
			temp_r = temp_r->next;
		}
		temp = temp->next;
	}
	return (0);
}

void	init_all_structs(t_input **input, t_progres **progree, char **env)
{
	*input = malloc(sizeof(t_input));
	*progree = malloc(sizeof(t_progres));
	init_struct(*input);
	(*progree)->i = 0;
	(*progree)->envp = env;
}

char	*read_input(void)
{
	char	*str;

	str = readline("minishell$>");
	if (!str)
		exit(g_var);
	if (!str[0])
	{
		free(str);
		return (NULL);
	}
	if (check_spaces(str))
	{
		free(str);
		return (NULL);
	}	
	return (str);
}

int	main(int ac, char **av, char **envp)
{
	char		**env;
	t_progres	*progree;
	t_input		*input;

	(void)av;
	if (ac == 1)
	{
		env = init_env(envp);
		g_var = 0;
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signals();
			init_all_structs(&input, &progree, env);
			progree->input = read_input();
			if (progree->input != NULL)
			{
				add_history(progree->input);
				step_one(progree, input);
			}
			env = progree->envp;
			ft_free1(progree, input);
		}
	}
	return (0);
}
