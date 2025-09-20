/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:35:15 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/24 00:37:26 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	char		value;
	size_t		i;

	str = (const char *)s;
	value = (char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == value)
			return ((void *)(&str[i]));
		i++;
	}
	return (NULL);
}
