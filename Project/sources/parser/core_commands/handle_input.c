/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:18:02 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:18:02 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	open_infile(t_redirect *io, char *file, char *original_filename)
{
	if (!remove_old_file_ref(io, true))
		return ;
	io->in_file_name = ft_strdup(file);
	if (!io->in_file_name)
		return ;
	if (io->in_file_name && io->in_file_name[0] == '\0')
	{
		errmsg_cmd(original_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->in_file_name, O_RDONLY);
	if (io->fd_in == -1)
		errmsg_cmd(io->in_file_name, NULL, strerror(errno), false);
}

void	handle_input(t_command **last_cmd, t_token **list_token)
{
	t_token		*tmp;
	t_command	*cmd;

	tmp = *list_token;
	cmd = get_last_command(*last_cmd);
	init_redir_struct(cmd);
	open_infile(cmd->_io_redirect,
		tmp->next->token_content,
		tmp->next->original_content);
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*list_token = tmp;
}
