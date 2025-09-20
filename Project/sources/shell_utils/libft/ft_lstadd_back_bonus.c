/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:01:29 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/10 07:09:15 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*_noeud;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		_noeud = ft_lstlast(*lst);
		_noeud->next = new;
	}
}
