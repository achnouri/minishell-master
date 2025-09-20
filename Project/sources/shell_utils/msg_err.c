/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:28:51 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/22 18:59:03 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	add_detail_quotes(char *command)
{
	if (!command)
		return (false);
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

int	errmsg_cmd(char *cmd_name, char *error_detail,
		char *error_text, int error_code)
{
	char	*full_error_msg;
	bool	should_quote_detail;

	should_quote_detail = add_detail_quotes(cmd_name);
	full_error_msg = ft_strdup("minishell: ");
	if (cmd_name != NULL)
	{
		full_error_msg = join_strings(full_error_msg, cmd_name);
		full_error_msg = join_strings(full_error_msg, ": ");
	}
	if (error_detail != NULL)
	{
		printf("");
		if (should_quote_detail)
			full_error_msg = join_strings(full_error_msg, "`");
		full_error_msg = join_strings(full_error_msg, error_detail);
		if (should_quote_detail)
			full_error_msg = join_strings(full_error_msg, "'");
		full_error_msg = join_strings(full_error_msg, ": ");
	}
	full_error_msg = join_strings(full_error_msg, error_text);
	ft_putendl_fd(full_error_msg, STDERR_FILENO);
	safe_free(full_error_msg);
	return (error_code);
}

void	display_error(char *error_msg_type, char *specifics, int use_quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = join_strings(msg, error_msg_type);
	if (use_quotes)
		msg = join_strings(msg, " `");
	else
		msg = join_strings(msg, ": ");
	msg = join_strings(msg, specifics);
	if (use_quotes)
		msg = join_strings(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	safe_free(msg);
}

void	lst_delone_cmd(t_command *lst, void (*del)(void *))
{
	if (lst->cmd_name)
		(*del)(lst->cmd_name);
	if (lst->arguments)
		free_string_array(lst->arguments);
	if (lst->pipe_fds)
		(*del)(lst->pipe_fds);
	if (lst->_io_redirect)
		free_io(lst->_io_redirect);
	(*del)(lst);
}

void	lst_clear_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		lst_delone_cmd(*lst, del);
		*lst = temp;
	}
}
