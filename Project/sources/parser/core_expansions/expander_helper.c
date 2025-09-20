/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 10:14:47 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 10:14:47 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->token_status == CRR_QTS)
		(*token_node)->token_status = SINGLE_QUOTE;
	else if (c == '\"' && (*token_node)->token_status == CRR_QTS)
		(*token_node)->token_status = DOUBLE_QUOTE;
	else if (c == '\'' && (*token_node)->token_status == SINGLE_QUOTE)
		(*token_node)->token_status = CRR_QTS;
	else if (c == '\"' && (*token_node)->token_status == DOUBLE_QUOTE)
		(*token_node)->token_status = CRR_QTS;
}

bool	is_char_between_double_quotes(char *content, int i)
{
	if (i > 0)
	{
		if (content[i - 1] == '\"' && content[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

static char	*handle_env_var(t_token *token, t_shell_data *data, char *var_name)
{
	char	*val;

	if (var_exist(data, var_name) == 0)
	{
		if (token)
			token->env_var_exist = true;
		val = search_value_env(data, var_name);
	}
	else if (var_name[0] == '?' && var_name[1] == '=')
		val = ft_itoa(get_status_exit_in_sig(-1));
	else
		val = NULL;
	return (val);
}

char	*get_variable_value(t_token *token,
		char *content, t_shell_data *data)
{
	char	*val_name;
	char	*var_name;

	if (!content)
		return (NULL);
	var_name = identify_var(content);
	if (var_name)
		val_name = handle_env_var(token, data, var_name);
	else
		val_name = NULL;
	safe_free(var_name);
	return (val_name);
}
