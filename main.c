/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:38:03 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/10 04:13:06 by ybachaki         ###   ########.fr       */
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
		return (NULL);
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

void	execution(t_input *input, char **env)
{
	signal(2, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!input->pipe)
		execute_single_cmd(input, env);
	else
		ft_pipes(input, env);
}

int	input_checker(t_input *input)
{
	t_input		*temp;
	t_redirect	*temp_r;

	temp = input;
	while (temp)
	{
		// if (!temp->cmd)
		// 	return (1);
		if (temp->pipe == 1 && temp->next == NULL)
			return (1);
		temp_r = temp->redirrections;
		while (temp_r)
		{
			if (temp_r->fd == -1 && temp_r->delimiter == NULL)
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

	str = readline("minishell>>");
	if (!str)
		exit(0);
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

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i])
		return (0);
	else
		return (1);	
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
			signals();
			init_all_structs(&input, &progree, env);
			progree->input = read_input();
			if (progree->input != NULL)
			{
				add_history(progree->input);
				step_one(progree, input);
			}
			ft_free1(progree, input);
		}
	}
	return (0);
}
