/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:17:22 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:17:22 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ensure_args_array(t_shell_data *data)
{
	t_command	*cmd_node;

	if (!data || !data->cmd)
		return ;
	cmd_node = data->cmd;
	while (cmd_node && cmd_node->cmd_name)
	{
		if (!cmd_node->arguments)
		{
			cmd_node->arguments = ft_malloc(sizeof * cmd_node->arguments * 2);
			if (!cmd_node->arguments)
				return ;
			cmd_node->arguments[0] = ft_strdup(cmd_node->cmd_name);
			cmd_node->arguments[1] = NULL;
		}
		cmd_node = cmd_node->next;
	}
	cmd_node = get_last_command(data->cmd);
}

int	append_command_arguments(t_token **current_token, t_command *command)
{
	if (!ft_strcmp(command->cmd_name, "echo"))
	{
		if (command->arguments == NULL)
			return (create_echo_arguments(current_token, command));
		else
			return (append_next_echo_argument(current_token, command));
	}
	else
	{
		if (command && !(command->arguments))
			return (creat_command_arguments(current_token, command));
		else
			return (append_next_command_argument(current_token, command));
	}
	return (SUCCESS);
}

void	split_and_fill_command_args(t_command *last_cmd, char *cmd_str)
{
	t_token	*new_tokens;
	char	**strs;
	int		i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	if (strs[0] && last_cmd->cmd_name == NULL)
	{
		last_cmd->cmd_name = ft_strdup(strs[0]);
		i = 1;
	}
	else
		i = 0;
	while (strs[i++])
		if (strs[i])
			lst_add_back_token(&new_tokens, lst_new_token(ft_strdup(strs[i]),
					NULL, ARG, CRR_QTS));
	lst_add_back_token(&new_tokens, lst_new_token(NULL, NULL, END,
			CRR_QTS));
	append_command_arguments(&new_tokens, last_cmd);
	delete_token_chain(&new_tokens, &safe_free);
	free_string_array(strs);
}

bool	should_set_command_name(t_token *tmp, t_command *last_cmd)
{
	return (tmp->previous == NULL
		|| (tmp->previous && tmp->previous->token_type == PIPE)
		|| last_cmd->cmd_name == NULL);
}

void	process_command_name(t_token **tmp, t_command *last_cmd)
{
	if ((*tmp)->token_type == VAR && fih_space((*tmp)->token_content))
		split_and_fill_command_args(last_cmd, (*tmp)->token_content);
	else
		last_cmd->cmd_name = ft_strdup((*tmp)->token_content);
	*tmp = (*tmp)->next;
}
