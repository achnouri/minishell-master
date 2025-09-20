/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:21:07 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:21:07 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_shell_separator(char *input_line, int index)
{
	if (((input_line[index] > 8 && input_line[index] < 14)
			|| input_line[index] == 32))
		return (SPACE_);
	else if (input_line[index] == '|')
		return (PIPE);
	else if (input_line[index] == '<' && input_line[index + 1] == '<')
		return (HEREDOC);
	else if (input_line[index] == '>' && input_line[index + 1] == '>')
		return (APPEND);
	else if (input_line[index] == '<')
		return (INPUT);
	else if (input_line[index] == '>')
		return (TRUNC);
	else if (input_line[index] == '\0')
		return (END);
	else
		return (0);
}

int	update_quote_status(char *input_line, int current_status_quote, int pos)
{
	if (input_line[pos] == '\'' && current_status_quote == CRR_QTS)
		current_status_quote = SINGLE_QUOTE;
	else if (input_line[pos] == '\"' && current_status_quote == CRR_QTS)
		current_status_quote = DOUBLE_QUOTE;
	else if (input_line[pos] == '\'' && current_status_quote == SINGLE_QUOTE)
		current_status_quote = CRR_QTS;
	else if (input_line[pos] == '\"' && current_status_quote == DOUBLE_QUOTE)
		current_status_quote = CRR_QTS;
	return (current_status_quote);
}

static int	create_double_separator(char *input_line, t_token **lst_token,
	int index, int token_type)
{
	int		pos;
	char	*separator;

	pos = 0;
	separator = ft_malloc(sizeof(char) * 3);
	if (!separator)
		return (1);
	while (pos < 2)
		separator[pos++] = input_line[index++];
	separator[pos] = '\0';
	lst_add_back_token(lst_token, lst_new_token(separator, NULL, token_type,
			CRR_QTS));
	return (0);
}

static int	create_single_separator(char *input_line, t_token **lst_token,
	int index, int token_type)
{
	int		pos;
	char	*separator;

	pos = 0;
	separator = ft_malloc(sizeof(char) * 2);
	if (!separator)
		return (1);
	while (pos < 1)
		separator[pos++] = input_line[index++];
	separator[pos] = '\0';
	lst_add_back_token(lst_token, lst_new_token(separator, NULL, token_type,
			CRR_QTS));
	return (0);
}

int	save_token_separator(char *input_line, t_token **lst_token, int index,
	int token_type)
{
	if (token_type == APPEND || token_type == HEREDOC)
		return (create_double_separator(input_line, lst_token, index,
				token_type));
	else
		return (create_single_separator(input_line, lst_token, index,
				token_type));
}
