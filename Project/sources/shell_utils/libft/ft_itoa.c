/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:19:04 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/23 23:24:08 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_is_zero(void)
{
	char	*str;

	str = (char *) malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static int	ft_calcul_len(int n)
{
	int	lengh;

	if (n == 0)
		return (1);
	if (n < 0)
		lengh = 1;
	else
		lengh = 0;
	while (n != 0)
	{
		n = n / 10;
		lengh++;
	}
	return (lengh);
}

char	*ft_itoa(int n)
{
	int				lengh;
	char			*str;
	unsigned int	num;

	lengh = ft_calcul_len(n);
	if (n == 0)
	{
		str = ft_is_zero();
		return (str);
	}
	str = (char *)malloc((lengh + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[lengh] = '\0';
	num = (unsigned int) n;
	if (n < 0)
		num = (unsigned int) -n;
	if (n < 0)
		str[0] = '-';
	while (lengh-- > 0 && num > 0)
	{
		str[lengh] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}
