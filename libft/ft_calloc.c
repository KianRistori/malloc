/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:44:06 by kristori          #+#    #+#             */
/*   Updated: 2022/10/05 15:29:42 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	void	*ris;

	i = nmemb * size;
	if (nmemb != 0 && i / nmemb != size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (NULL);
	ris = malloc(nmemb * size);
	ft_memset(ris, 0, (nmemb * size));
	return (ris);
}
