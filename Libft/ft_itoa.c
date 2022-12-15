/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 21:37:20 by aoukhart          #+#    #+#             */
/*   Updated: 2021/11/23 01:52:27 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill(unsigned int x, int n, unsigned int size, char *str)
{
	unsigned int	x1;

	x1 = x;
	while (x1 != 0 && ++size)
		x1 /= 10;
	if (n < 0)
		size++;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > 0 && x > 0)
	{
		str[size - 1] = ((x % 10) + 48);
		x /= 10;
		size--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	x;
	unsigned int	size;

	str = NULL;
	if (n < 0)
		x = n * -1;
	else
		x = n;
	if (n == 0)
		return (ft_strdup("0"));
	size = 0;
	return (ft_fill(x, n, size, str));
}

// int main()
// {
//     printf("%s\n", ft_itoa(123456789));
//     return 0;
// }
