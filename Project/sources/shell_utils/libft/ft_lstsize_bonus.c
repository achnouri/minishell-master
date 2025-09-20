/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:36:32 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/24 00:37:23 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*courant;
	int		compteur;

	compteur = 0;
	courant = lst;
	while (courant != NULL)
	{
		compteur++;
		courant = courant->next;
	}
	return (compteur);
}
