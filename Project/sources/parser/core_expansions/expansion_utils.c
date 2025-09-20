/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 10:14:12 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 10:14:12 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*search_value_env(t_shell_data *data, char *var_name)
{
	char	*value;
	int		i;
	int		lengh;

	i = 0;
	lengh = ft_strlen(var_name);
	while (data->env__[i])
	{
		if (ft_strncmp(data->env__[i], var_name, lengh) == 0)
			break ;
		i++;
	}
	if (!data->env__[i])
		return (NULL);
	value = ft_strdup(data->env__[i] + lengh);
	return (value);
}

int	var_exist(t_shell_data *data, char *var)
{
	int	i;
	int	lengh;

	i = 0;
	lengh = ft_strlen(var);
	while (data->env__[i])
	{
		if (ft_strncmp(data->env__[i], var, lengh) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	calculate_var_name_length(char *content)
{
	int	index;
	int	length;

	index = 0;
	length = 0;
	while (content[index] && content[index] != '$')
		index++;
	if (!content[index])
		return (0);
	index++;
	if (content[index] && ((content[index] >= '0' && content[index] <= '9')
			|| content[index] == '?'))
		return (1);
	while (content[index] && is_valid_var_char(content[index]))
	{
		length++;
		index++;
	}
	return (length);
}

char	*identify_var(char *content)
{
	char	*var_without_dollar;
	int		i;
	int		lengh;
	int		start;
	char	*tmp;

	(1) && (i = -1, start = 0);
	while (content && content[++i])
	{
		if (content[i] == '$')
		{
			start = i + 1;
			break ;
		}
	}
	lengh = calculate_var_name_length(content);
	var_without_dollar = ft_substr(content, start, lengh);
	if (!var_without_dollar)
		return (NULL);
	tmp = ft_strjoin(var_without_dollar, "=");
	if (!tmp)
		return (safe_free(var_without_dollar), NULL);
	safe_free(var_without_dollar);
	var_without_dollar = tmp;
	return (var_without_dollar);
}

char	*get_new_token_string(char *content, char *value_v, int new_str_length,
		int index)
{
	int		c_idx;
	int		new_index;
	char	*new_str;

	c_idx = 0;
	new_index = 0;
	new_str = ft_malloc(sizeof(char) * new_str_length);
	if (!new_str)
		return (NULL);
	while (content[c_idx])
	{
		if (content[c_idx] == '$' && c_idx == index)
		{
			copy_var_value(new_str, value_v, &new_index);
			c_idx = c_idx + calculate_var_name_length(content + index) + 1;
			if (content[c_idx] == '\0')
				break ;
		}
		new_str[new_index++] = content[c_idx++];
	}
	new_str[new_index] = '\0';
	return (new_str);
}
