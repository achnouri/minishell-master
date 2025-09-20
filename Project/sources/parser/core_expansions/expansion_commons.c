/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_commons.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:37:02 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/13 17:41:23 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_separator_char(char c)
{
	if (c == '$' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	return (true);
}

void	copy_var_value(char *new_str, char *value_v, int *new_index)
{
	int	value_index;

	value_index = 0;
	while (value_v[value_index])
	{
		new_str[*new_index] = value_v[value_index];
		value_index++;
		(*new_index)++;
	}
}
