/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:21:02 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:21:02 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	lst_add_back_token(t_token **lst_token, t_token *new_node_token)
{
	t_token	*head;

	head = *lst_token;
	if (head == NULL)
	{
		*lst_token = new_node_token;
		return ;
	}
	if (lst_token && *lst_token && new_node_token)
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node_token;
		new_node_token->previous = head;
	}
}

t_token	*lst_new_token(char *extracted_word, char *original, int type,
	int status_quote)
{
	t_token	*new_node;

	new_node = ft_malloc(sizeof(t_token) * 1);
	if (!new_node)
		return (NULL);
	new_node->token_content = extracted_word;
	new_node->original_content = original;
	new_node->env_var_exist = false;
	new_node->token_type = type;
	new_node->token_status = status_quote;
	new_node->should_concatenate = false;
	new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}
