/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:52:02 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/13 13:54:04 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_operator_clash(t_token *lst_token)
{
	if (lst_token->previous)
	{
		if (lst_token->token_type == PIPE
			&& lst_token->previous->token_type == PIPE)
			return (true);
		if (lst_token->token_type > PIPE
			&& lst_token->previous->token_type > PIPE)
			return (true);
		if (lst_token->token_type == END
			&& lst_token->previous->token_type >= PIPE)
			return (true);
		if (lst_token->token_type == PIPE
			&& lst_token->previous->token_type > PIPE)
			return (true);
		if (lst_token->token_type > PIPE
			&& lst_token->previous->token_type == PIPE)
			return (true);
	}
	return (false);
}

static void	print_syntax_error(t_token *tmp)
{
	if (tmp->token_type == END && tmp->previous
		&& tmp->previous->token_type > PIPE)
	{
		display_error(
			"syntax error near unexpected token",
			"newline", true);
	}
	else if (tmp->token_type == END && tmp->previous)
	{
		display_error(
			"syntax error near unexpected token",
			tmp->previous->token_content, true);
	}
	else
	{
		display_error(
			"syntax error near unexpected token",
			tmp->token_content, true);
	}
}

int	validate_syntax_errors(t_token **lst_token)
{
	t_token	*tmp;

	tmp = *lst_token;
	if (!lst_token || !*lst_token)
		return (FAILURE);
	while (tmp)
	{
		if (is_operator_clash(tmp) == true)
		{
			print_syntax_error(tmp);
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void	detect_env_variable(t_token **lst_token)
{
	int	i;

	i = 0;
	while ((*lst_token)->token_content[i])
	{
		if ((*lst_token)->token_content[i] == '$')
		{
			if ((*lst_token)->previous
				&& (*lst_token)->previous->token_type == HEREDOC)
				break ;
			(*lst_token)->token_type = VAR;
			return ;
		}
		i++;
	}
}

int	check_env_and_syntax_errors(t_token **lst_token)
{
	t_token	*tmp;

	tmp = *lst_token;
	if (tmp->token_type == PIPE)
	{
		display_error(
			"syntax error near unexpected token",
			tmp->token_content, true);
		return (FAILURE);
	}
	while (tmp)
	{
		detect_env_variable(&tmp);
		if (validate_syntax_errors(&tmp) == FAILURE)
			return (FAILURE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
