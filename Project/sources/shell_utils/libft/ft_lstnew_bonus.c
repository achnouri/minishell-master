/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:36:14 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/23 23:24:17 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nouvel_element;

	nouvel_element = (t_list *)malloc(sizeof(t_list));
	if (!nouvel_element)
		return (NULL);
	nouvel_element->content = content;
	nouvel_element->next = NULL;
	return (nouvel_element);
}
