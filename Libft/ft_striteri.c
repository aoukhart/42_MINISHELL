/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:36:32 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/25 00:59:29 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// void	lower(unsigned int i, char *s)
// {
// 	if (*s >= 'A' && *s <= 'Z')
// 		*s += 32;
// }
// int main()
// {
// 	char str[] = "AnAS";
// 	ft_striteri(str, &lower);
// 	printf("%s\n", str);
// 	return (0);
// }
