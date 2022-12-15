/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:59:09 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/25 03:38:15 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	i = ft_strlen(dst);
	j = 0;
	if (dstsize > ft_strlen(dst))
		ret = ft_strlen(dst) + ft_strlen(src);
	else
		ret = dstsize + ft_strlen(src);
	while ((i < dstsize - 1) && src[j] && dstsize != 0)
		dst[i++] = src[j++];
	if (dstsize > i)
		dst[i] = '\0';
	return (ret);
}

// int main()
// {
// 	char dest[] = "123";
// 	printf("%zu\n", strlcat(dest, "lorem", 4));
// 	return 0;
// }
