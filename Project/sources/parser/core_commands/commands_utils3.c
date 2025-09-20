/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:17:32 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:17:32 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**copy_in_args_new(int arg_count, char **args_new, t_command *cmd,
			t_token *cur_tok)
{
	int	i;

	i = 0;
	while (i < arg_count)
	{
		args_new[i] = cmd->arguments[i];
		i++;
	}
	while (cur_tok->token_type == ARG || cur_tok->token_type == VAR)
	{
		if (cur_tok->should_concatenate)
			args_new[i] = concat_vars(&cur_tok);
		else
			args_new[i] = ft_strdup(cur_tok->token_content);
		i++;
		cur_tok = cur_tok->next;
	}
	args_new[i] = NULL;
	return (args_new);
}

int	append_next_echo_argument(t_token **current_token, t_command *cmd)
{
	int		old_len;
	int		new_len;
	char	**args_new;
	t_token	*tmp;

	clean_empty_var_args(current_token);
	tmp = *current_token;
	new_len = count_argument_tokens(tmp);
	old_len = 0;
	while (cmd->arguments[old_len])
		old_len++;
	args_new = ft_malloc(sizeof(char *) * (new_len + old_len + 1));
	if (!args_new)
		return (FAILURE);
	args_new = copy_in_args_new(old_len, args_new, cmd, tmp);
	free(cmd->arguments);
	cmd->arguments = args_new;
	while (tmp->token_type == ARG || tmp->token_type == VAR)
		tmp = tmp->next;
	*current_token = tmp;
	return (SUCCESS);
}

void	clean_empty_var_args(t_token **token_list)
{
	t_token	*current;

	current = *token_list;
	while (current && (current->token_type == ARG
			|| current->token_type == VAR))
	{
		if (current->token_type == VAR && current->token_content[0] == '\0'
			&& current->env_var_exist == false)
		{
			current = current->next;
			if (current == (*token_list)->next)
				*token_list = (*token_list)->next;
			delete_token_node(current->previous, safe_free);
		}
		else
			current = current->next;
	}
}

int	count_argument_tokens(t_token *current_token)
{
	int	i;

	i = 0;
	while (current_token && (current_token->token_type == ARG
			|| current_token->token_type == VAR))
	{
		if (current_token->token_type == VAR
			&& current_token->should_concatenate == true)
		{
			while (current_token->token_type == VAR
				&& current_token->should_concatenate == true)
				current_token = current_token->next;
			i++;
		}
		else
		{
			i++;
			current_token = current_token->next;
		}
	}
	return (i);
}

int	create_echo_arguments(t_token **current_token, t_command *last_cmd)
{
	int		argument_count;
	t_token	*tmp;
	int		i;

	clean_empty_var_args(current_token);
	tmp = *current_token;
	argument_count = count_argument_tokens(tmp);
	last_cmd->arguments = ft_malloc(sizeof(char *) * (argument_count + 2));
	if (!last_cmd->arguments)
		return (FAILURE);
	i = 0;
	last_cmd->arguments[i++] = ft_strdup(last_cmd->cmd_name);
	while (tmp->token_type == ARG || tmp->token_type == VAR)
	{
		if (tmp->should_concatenate == true)
			last_cmd->arguments[i] = concat_vars(&tmp);
		else
			last_cmd->arguments[i] = ft_strdup(tmp->token_content);
		i++;
		tmp = tmp->next;
	}
	last_cmd->arguments[i] = NULL;
	*current_token = tmp;
	return (SUCCESS);
}
