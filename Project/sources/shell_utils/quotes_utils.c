/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:36:43 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/23 23:25:46 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	exit_quote_mode_if_closing_quote(t_token **token_ptr, int *i)
{
	if (((*token_ptr)->token_content[*i] == '\''
			&& (*token_ptr)->token_status == SINGLE_QUOTE)
		|| ((*token_ptr)->token_content[*i] == '\"'
			&& (*token_ptr)->token_status == DOUBLE_QUOTE))
	{
		(*token_ptr)->token_status = CRR_QTS;
		(*i)++;
		return (true);
	}
	return (false);
}

static int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == CRR_QTS)
		{
			if (str[i] == '\'')
				status = SINGLE_QUOTE;
			if (str[i] == '\"')
				status = DOUBLE_QUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SINGLE_QUOTE)
			|| (str[i] == '\"' && status == DOUBLE_QUOTE))
		{
			status = CRR_QTS;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	new_line = ft_malloc(sizeof(char)
			* count_len((*token_node)->token_content, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->token_content[i])
	{
		if (if_quotes_and_correct_quotes(token_node, i) == true)
		{
			update_token_status_on_quote(token_node, &i);
			continue ;
		}
		else if (exit_quote_mode_if_closing_quote(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->token_content[i++];
	}
	new_line[j] = '\0';
	safe_free((*token_node)->token_content);
	(*token_node)->token_content = new_line;
	(*token_node)->should_concatenate = true;
	return (0);
}

int	process_tokens_remove_quotes(t_shell_data *data)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = data->token;
	while (current_token)
	{
		next_token = current_token->next;
		if (contains_quotes(current_token->token_content) == true
			&& (!current_token->previous
				|| (current_token->previous
					&& current_token->previous->token_type != HEREDOC)))
		{
			remove_quotes(&current_token);
		}
		current_token = next_token;
	}
	return (0);
}
