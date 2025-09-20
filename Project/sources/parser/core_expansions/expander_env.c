/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 10:14:41 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 10:14:41 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*collapse_spaces(const char *value)
{
	char	*result;
	int		i;
	int		j;
	bool	in_space;

	(1) && (i = -1, j = 0, in_space = false);
	result = ft_malloc(ft_strlen(value) + 1);
	while (value[++i])
	{
		if (value[i] == ' ' || value[i] == '\t')
		{
			if (!in_space)
			{
				result[j++] = ' ';
				in_space = true;
			}
		}
		else
		{
			result[j++] = value[i];
			in_space = false;
		}
	}
	result[j] = '\0';
	return (result);
}

int	handle_no_quotes_case(t_token **token_node, char *value_v,
		char *content, int index)
{
	char	*collapsed;

	if (value_v && *value_v)
	{
		collapsed = collapse_spaces(value_v);
		value_v = collapsed;
	}
	if (replace_remove_value_v_token(token_node, content,
			value_v, index) == NULL)
		return (1);
	return (0);
}

int	replace_var_with_value_in_token(t_token **token_node, char *value_v,
		int index, int inside_quotes)
{
	if (value_v == NULL)
	{
		if (remove_variable_from_token(token_node,
				(*token_node)->token_content, index))
			return (safe_free(value_v), 1);
	}
	else
	{
		if (inside_quotes == DOUBLE_QUOTE)
		{
			if (handle_quotes_case(token_node, value_v,
					(*token_node)->token_content, index))
				return (1);
		}
		else
		{
			if (handle_no_quotes_case(token_node, value_v,
					(*token_node)->token_content, index))
				return (1);
		}
	}
	return (safe_free(value_v), 0);
}

static int	process_token(t_token **tmp, t_shell_data *data)
{
	int	i;

	i = 0;
	while ((*tmp)->token_content && (*tmp)->token_content[i])
	{
		update_status(tmp, (*tmp)->token_content[i]);
		if ((*tmp)->token_content[i] == '$'
			&& is_separator_char((*tmp)->token_content[i + 1]) == false
			&& is_char_between_double_quotes((*tmp)->token_content, i)
			== false && ((*tmp)->token_status == CRR_QTS
				|| (*tmp)->token_status == DOUBLE_QUOTE))
		{
			replace_var_with_value_in_token(tmp,
				get_variable_value(*tmp, (*tmp)->token_content + i, data),
				i, (*tmp)->token_status);
		}
		else
			i++;
	}
	return (0);
}

int	expand_env_vars(t_shell_data *data, t_token **lst_token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *lst_token;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->token_type == VAR)
			process_token(&tmp, data);
		tmp = next;
	}
	return (0);
}
