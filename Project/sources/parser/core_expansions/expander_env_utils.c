/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 10:14:20 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 10:14:20 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_variable_split_utils(t_token **token_node,
		char **split_values, t_token *prev, t_token *next)
{
	int		i;
	t_token	*new_tok;

	i = 0;
	while (split_values[i])
	{
		new_tok = lst_new_token(ft_strdup(split_values[i]), NULL, ARG,
				CRR_QTS);
		if (prev)
		{
			prev->next = new_tok;
			new_tok->previous = prev;
		}
		prev = new_tok;
		i++;
	}
	if (prev)
		prev->next = next;
	if (next)
		next->previous = prev;
	*token_node = prev;
	return (0);
}

char	*replace_remove_value_v_token(t_token **token_node, char *content,
		char *value_v, int idx)
{
	char	*update_str;
	int		update_str_lengh;

	update_str_lengh = ft_strlen(content) - calculate_var_name_length(content
			+ idx) + ft_strlen(value_v);
	update_str = get_new_token_string(content, value_v, update_str_lengh, idx);
	if (token_node && *token_node)
	{
		safe_free((*token_node)->token_content);
		(*token_node)->token_content = update_str;
	}
	return (update_str);
}

int	handle_quotes_case(t_token **token_node, char *value_v,
		char *content, int index)
{
	if (replace_remove_value_v_token(token_node, content, value_v, index)
		== NULL)
	{
		safe_free(value_v);
		return (1);
	}
	return (0);
}

static int	remove_variable_from_token_utils(t_token **token_node,
		char *content, int index, char *new_content)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '$' && i == index)
		{
			i = i + calculate_var_name_length(content + index) + 1;
			if (content[i] == '\0')
				break ;
		}
		new_content[j++] = content[i++];
	}
	new_content[j] = '\0';
	safe_free((*token_node)->token_content);
	(*token_node)->token_content = new_content;
	return (0);
}

int	remove_variable_from_token(t_token **token_node, char *content,
		int index)
{
	int		length;
	char	*new_content;

	length = ft_strlen(content) - calculate_var_name_length(content + index);
	new_content = (char *)ft_malloc(sizeof(char) * (length + 1));
	if (!new_content)
		return (1);
	return (remove_variable_from_token_utils(token_node, content, index,
			new_content));
}
