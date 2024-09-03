/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:24:04 by kristori          #+#    #+#             */
/*   Updated: 2022/10/05 14:42:49 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	size_t	i;

	i = 0;
	len_little = ft_strlen(little);
	if (!len_little)
		return ((char *)big);
	while (big[i] && len_little <= len--)
	{
		if (big[i] == little[0])
		{
			if (!ft_strncmp(&big[i], little, len_little))
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
