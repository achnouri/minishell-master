/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:18:08 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:18:08 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_pipe(t_command **cmd, t_token **list_token)
{
	t_command	*last_cmd;

	last_cmd = get_last_command(*cmd);
	last_cmd->has_pipe = true;
	lst_add_back_cmd(&last_cmd, lst_new_cmd(false));
	*list_token = (*list_token)->next;
}
