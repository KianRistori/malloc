/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:22:24 by kristori          #+#    #+#             */
/*   Updated: 2022/10/06 16:04:01 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ris;
	int		i;

	if (!s || !f)
		return (NULL);
	ris = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!ris)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ris[i] = f(i, s[i]);
		i++;
	}
	ris[i] = '\0';
	return (ris);
}
