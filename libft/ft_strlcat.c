/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:30:47 by kristori          #+#    #+#             */
/*   Updated: 2022/10/10 09:58:09 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j] && j < size)
		j++;
	while ((src[k] && (j + k + 1) < size))
	{
		dest[j + k] = src[k];
		k++;
	}
	if (j != size)
		dest[j + k] = '\0';
	return (j + ft_strlen(src));
}
