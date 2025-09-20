/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 08:45:13 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/24 00:37:34 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*destination;
	const char	*source;

	destination = (char *)dst;
	source = (const char *)src;
	if (destination == source || len == 0)
		return (dst);
	if (destination < source)
	{
		i = 0;
		while (len--)
		{
			destination[i] = source[i];
			i++;
		}
	}
	else
	{
		while (len--)
			destination[len] = source[len];
	}
	return (dst);
}
