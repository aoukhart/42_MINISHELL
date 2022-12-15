/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:43:46 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/25 03:29:04 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*d1;

	s1 = (unsigned char *)src;
	d1 = (unsigned char *)dst;
	if (dst == NULL && src == NULL)
		return (0);
	if (s1 < d1)
	{
		while (len--)
			d1[len] = s1[len];
	}
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
// int main () 
// {
// 	char s[] = {65, 66, 67, 68, 69, 0, 45};
// 	char s0[] = { 0,  0,  0,  0,  0,  0, 0};
//     printf("%s\n", ft_memmove(s0, s, 7));
//     return(0);
// }