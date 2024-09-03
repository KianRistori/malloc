/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:53:05 by kristori          #+#    #+#             */
/*   Updated: 2022/10/05 15:30:17 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ris;
	int		i;

	i = 0;
	ris = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!ris)
		return (ris);
	while (s[i])
	{
		ris[i] = s[i];
		i++;
	}
	ris[i] = '\0';
	return (ris);
}
