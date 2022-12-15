/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:34:30 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/24 22:41:10 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	cat = malloc (((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!cat)
		return (NULL);
	while (j < ft_strlen(s1))
		cat[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		cat[i++] = s2[j++];
	cat[i] = '\0';
	return (cat);
}
// int main()
// {
//     printf("%s", ft_strjoin("1234", "5678"));
//     return 0;
// }