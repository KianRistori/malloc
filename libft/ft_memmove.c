/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:17:20 by kristori          #+#    #+#             */
/*   Updated: 2022/10/05 15:30:01 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	c1 = (unsigned char *)dest;
	c2 = (unsigned char *)src;
	i = 0;
	if (c1 > c2)
	{
		while (i < n)
		{
			c1[n - 1] = c2[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			c1[i] = c2[i];
			i++;
		}
	}
	return (dest);
}
