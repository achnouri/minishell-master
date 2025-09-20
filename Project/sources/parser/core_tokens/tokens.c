/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:21:13 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:21:13 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	save_token_word(t_token **token_lst, char *input_line, int index,
	int start_line)
{
	int		pos;
	char	*extracted_word;
	t_token	*new_node_token;

	pos = 0;
	extracted_word = ft_malloc(sizeof(char) * (index - start_line + 1));
	if (!extracted_word)
		return (1);
	while (start_line < index)
	{
		extracted_word[pos] = input_line[start_line];
		start_line++;
		pos++;
	}
	extracted_word[pos] = '\0';
	new_node_token = lst_new_token(extracted_word, ft_strdup(extracted_word),
			ARG, CRR_QTS);
	lst_add_back_token(token_lst, new_node_token);
	return (0);
}

int	save_separator_if_needed(char *input_line, int *index,
	int start_line, t_shell_data *data)
{
	int	token_type;

	(void)start_line;
	token_type = is_shell_separator(input_line, *index);
	if (token_type == PIPE || token_type == INPUT || token_type == TRUNC
		|| token_type == HEREDOC || token_type == END
		|| token_type == APPEND)
	{
		save_token_separator(input_line, &data->token, (*index), token_type);
		if (token_type == APPEND || token_type == HEREDOC)
			(*index)++;
	}
	return ((*index) + 1);
}

static int	extract_tokens(char *input_line, int *index, int start_line,
	t_shell_data *data)
{
	int	token_type;

	token_type = is_shell_separator(input_line, *index);
	if (token_type)
	{
		if (*index != 0 && is_shell_separator(input_line, (*index) - 1) == 0)
			save_token_word(&data->token, input_line, (*index), start_line);
		start_line = save_separator_if_needed(input_line, index, start_line,
				data);
	}
	return (start_line);
}

static int	handle_quote_error(int quotes_status)
{
	if (quotes_status == DOUBLE_QUOTE)
	{
		display_error("unexpected EOF while looking for matching",
			"\"", true);
		return (1);
	}
	else if (quotes_status == SINGLE_QUOTE)
	{
		display_error("unexpected EOF while looking for matching",
			"\'", true);
		return (1);
	}
	return (0);
}

int	tokens(t_shell_data *data, char *input_line)
{
	int	index;
	int	end_line;
	int	start_line;
	int	quotes_status;

	index = -1;
	start_line = 0;
	end_line = ft_strlen(input_line);
	quotes_status = CRR_QTS;
	while (++index <= end_line)
	{
		quotes_status = update_quote_status(input_line, quotes_status, index);
		if (quotes_status == CRR_QTS)
			start_line = extract_tokens(input_line, &index, start_line, data);
	}
	if (quotes_status != CRR_QTS)
		return (handle_quote_error(quotes_status));
	return (0);
}
