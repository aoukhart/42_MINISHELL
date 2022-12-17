/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:45:51 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/16 19:23:59 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	pwd(t_input *input, t_progres *progress)
{
	char	s[1052];

	(void)input;
	(void)progress;
	getcwd(s, sizeof (s));
	printf("%s\n", s);
}
