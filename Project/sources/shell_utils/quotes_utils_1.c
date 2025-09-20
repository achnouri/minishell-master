/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:14:34 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/19 00:54:10 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	contains_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

bool	if_quotes_and_correct_quotes(t_token **token_node, int i)
{
	if (((*token_node)->token_content[i] == '\'')
		|| ((*token_node)->token_content[i] == '\"'))
	{
		if ((*token_node)->token_status == CRR_QTS)
			return (true);
	}
	return (false);
}

void	update_token_status_on_quote(t_token **token_node, int *i)
{
	if ((*token_node)->token_content[*i] == '\'')
		(*token_node)->token_status = SINGLE_QUOTE;
	if ((*token_node)->token_content[*i] == '\"')
		(*token_node)->token_status = DOUBLE_QUOTE;
	(*i)++;
}
