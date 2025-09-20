/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:17:47 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:17:47 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	open_out_append(t_redirect *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->out_file_name = ft_strdup(file);
	if (io->out_file_name && io->out_file_name[0] == '\0' && var_filename)
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->out_file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->out_file_name, NULL, strerror(errno), false);
}

void	handle_append(t_command **cmd, t_token **list_token)
{
	t_command	*last_cmd;
	t_token		*tmp;

	tmp = *list_token;
	last_cmd = get_last_command(*cmd);
	init_redir_struct(last_cmd);
	open_out_append(last_cmd->_io_redirect,
		tmp->next->token_content,
		tmp->next->original_content);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*list_token = tmp;
}
