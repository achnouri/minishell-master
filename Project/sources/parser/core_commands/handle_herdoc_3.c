/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:45:27 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 23:31:20 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*erase_and_replace(t_token **token_node,
			char *str, char *var_value, int index)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - calculate_var_name_length(str + index)
			+ ft_strlen(var_value));
	newstr = get_new_token_string(str, var_value, newstr_size, index);
	if (token_node && *token_node)
	{
		safe_free((*token_node)->token_content);
		(*token_node)->token_content = newstr;
	}
	return (newstr);
}

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		str[0] = '\0';
	else
	{
		tmp = str;
		str = erase_and_replace(NULL, str, var_value, index);
		safe_free(tmp);
	}
	safe_free(var_value);
	return (str);
}

char	*var_expander_heredoc(t_shell_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_separator_char(str[i + 1]) == false
			&& is_char_between_double_quotes(str, i) == false)
		{
			str = replace_str_heredoc(str,
					get_variable_value(NULL, str + i, data), i);
		}
		else
			i++;
	}
	return (str);
}
