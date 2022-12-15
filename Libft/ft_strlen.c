/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:15:58 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/24 22:46:43 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
// int main()
// {
// 	printf("%zu", ft_strlen("12345");
// 	return 0;
// }
