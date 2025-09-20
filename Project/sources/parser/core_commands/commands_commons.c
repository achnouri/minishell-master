/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_commons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:17:09 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:17:09 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*concat_vars(t_token **token_courant)
{
	t_token	*tmp;
	char	*result;

	tmp = *token_courant;
	result = ft_strdup(tmp->token_content);
	while (tmp->token_type == VAR && tmp->next
		&& tmp->next->token_type == VAR
		&& tmp->next->should_concatenate == true)
	{
		result = ft_strjoin(result, tmp->next->token_content);
		tmp = tmp->next;
	}
	*token_courant = tmp;
	return (result);
}

int	count_simple_tokens(t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp && (tmp->token_type == ARG || tmp->token_type == VAR))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**copy_tokens_into_args(int len, char **args_new,
			t_command *last_cmd, t_token **token_node)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *token_node;
	while (i < len)
	{
		args_new[i] = last_cmd->arguments[i];
		i++;
	}
	while (tmp->token_type == ARG || tmp->token_type == VAR)
	{
		args_new[i] = ft_strdup(tmp->token_content);
		i++;
		tmp = tmp->next;
	}
	args_new[i] = NULL;
	return (args_new);
}

void	init_redir_struct(t_command *cmd)
{
	if (!cmd->_io_redirect)
	{
		cmd->_io_redirect = ft_malloc(sizeof * cmd->_io_redirect);
		if (!cmd->_io_redirect)
			return ;
		cmd->_io_redirect->in_file_name = NULL;
		cmd->_io_redirect->out_file_name = NULL;
		cmd->_io_redirect->break_delimiter = NULL;
		cmd->_io_redirect->has_quotes = false;
		cmd->_io_redirect->fd_in = -1;
		cmd->_io_redirect->fd_out = -1;
		cmd->_io_redirect->fd_stdin_backup = -1;
		cmd->_io_redirect->fd_stdout_backup = -1;
	}
}

void	init_cmd(t_command **cmd)
{
	(*cmd)->cmd_name = NULL;
	(*cmd)->cmd_path = NULL;
	(*cmd)->arguments = NULL;
	(*cmd)->has_pipe = false;
	(*cmd)->pipe_fds = 0;
	(*cmd)->previous = NULL;
	(*cmd)->next = NULL;
}
