/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kristori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:12:31 by kristori          #+#    #+#             */
/*   Updated: 2022/10/07 12:32:07 by kristori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ris;

	ris = (t_list *)malloc(sizeof(t_list));
	if (!ris)
		return (NULL);
	ris->content = content;
	ris->next = NULL;
	return (ris);
}
