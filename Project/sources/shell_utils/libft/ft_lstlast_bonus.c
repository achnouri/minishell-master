/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:40:39 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/24 00:37:18 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*courant;

	if (!lst)
	{
		return (NULL);
	}
	courant = lst;
	while (courant->next != NULL)
	{
		courant = courant->next;
	}
	return (courant);
}
