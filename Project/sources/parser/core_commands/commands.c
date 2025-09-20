/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:17:42 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:17:42 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_args(t_command **cmd, t_token **lst_token)
{
	t_token		*tmp;
	t_command	*last_cmd;

	tmp = *lst_token;
	while (tmp->token_type == ARG || tmp->token_type == VAR)
	{
		last_cmd = get_last_command(*cmd);
		if (should_set_command_name(tmp, last_cmd))
			process_command_name(&tmp, last_cmd);
		else
			append_command_arguments(&tmp, last_cmd);
	}
	*lst_token = tmp;
}

bool	handle_heredoc_token(t_shell_data *data, t_token **tmp)
{
	if (!check_line_limit_of_delimiters(data->line_input))
	{
		ft_putendl_fd("bash: maximum here-document count exceeded", 2);
		return (false);
	}
	if (handle_heredoc(data, tmp, &data->cmd) == false)
		return (false);
	*tmp = (*tmp)->next->next;
	return (true);
}

static void	process_token_types(t_shell_data *data, t_token **tmp)
{
	if ((*tmp)->token_type == ARG || (*tmp)->token_type == VAR)
		handle_args(&data->cmd, tmp);
	else if ((*tmp)->token_type == INPUT)
		handle_input(&data->cmd, tmp);
	else if ((*tmp)->token_type == TRUNC)
		handle_trunc(&data->cmd, tmp);
	else if ((*tmp)->token_type == APPEND)
		handle_append(&data->cmd, tmp);
	else if ((*tmp)->token_type == PIPE)
		handle_pipe(&data->cmd, tmp);
}

bool	process_heredoc(t_shell_data *data, t_token **tmp)
{
	if (!check_line_limit_of_delimiters(data->line_input))
	{
		ft_putendl_fd("bash: maximum here-document count exceeded", 2);
		return (false);
	}
	if (handle_heredoc(data, tmp, &data->cmd) == false)
		return (false);
	*tmp = (*tmp)->next->next;
	return (true);
}

bool	creat_commands(t_shell_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!tmp || tmp->token_type == END)
		return (true);
	while (tmp && tmp->next != NULL)
	{
		if (tmp == token)
			lst_add_back_cmd(&data->cmd, lst_new_cmd(false));
		if (tmp->token_type == HEREDOC)
		{
			if (!process_heredoc(data, &tmp))
				return (false);
			continue ;
		}
		else if (tmp->token_type == END)
			break ;
		else
			process_token_types(data, &tmp);
	}
	ensure_args_array(data);
	return (true);
}
