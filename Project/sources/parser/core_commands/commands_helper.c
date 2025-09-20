/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:17:17 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:17:17 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	lst_add_back_cmd(t_command **lst_cmd, t_command *new_node_cmd)
{
	t_command	*head;

	head = *lst_cmd;
	if (head == NULL)
	{
		*lst_cmd = new_node_cmd;
		return ;
	}
	if (lst_cmd && *lst_cmd && new_node_cmd)
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node_cmd;
		new_node_cmd->previous = head;
	}
}

t_command	*get_last_command(t_command *lst_cmd)
{
	while (lst_cmd->next != NULL)
		lst_cmd = lst_cmd->next;
	return (lst_cmd);
}

t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)ft_malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->has_pipe = value;
	init_cmd(&new_node);
	return (new_node);
}

void	delete_token_node(t_token *node, void (*del)(void *))
{
	if (del && node && node->token_content)
	{
		(*del)(node->token_content);
		node->token_content = NULL;
	}
	if (del && node && node->original_content)
	{
		(*del)(node->original_content);
		node->original_content = NULL;
	}
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;
	safe_free(node);
}

void	delete_token_chain(t_token **new_token, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*new_token != NULL)
	{
		tmp = (*new_token)->next;
		delete_token_node(*new_token, del);
		*new_token = tmp;
	}
}
