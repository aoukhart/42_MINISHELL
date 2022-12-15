/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:50:32 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/24 23:04:27 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(b + i) == (unsigned char)c)
			return ((void *)(b + i));
		i++;
	}
	return (NULL);
}
// int main()
// {
// 	printf("%s", ft_memchr("1234556789", '5', 6));
// 	return 0;
// }
