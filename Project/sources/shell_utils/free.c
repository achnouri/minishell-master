/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:32:36 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/23 22:07:52 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_io(t_redirect *io)
{
	if (!io)
		return ;
	reset_redirection(io);
	if (io->break_delimiter)
	{
		unlink(io->in_file_name);
		safe_free(io->break_delimiter);
	}
	if (io->in_file_name)
		safe_free(io->in_file_name);
	if (io->out_file_name)
		safe_free(io->out_file_name);
	if (io)
		safe_free(io);
}

void	free_shell_data(t_shell_data *data, bool clear_history)
{
	if (data && data->line_input)
	{
		safe_free(data->line_input);
		data->line_input = NULL;
	}
	if (data && data->token)
	{
		delete_token_chain(&data->token, &safe_free);
	}
	if (data && data->cmd)
	{
		lst_clear_cmd(&data->cmd, &safe_free);
	}
	if (clear_history == true)
	{
		if (data && data->current_dir)
			safe_free(data->current_dir);
		if (data && data->old_dir)
			safe_free(data->old_dir);
		if (data && data->env__)
			free_string_array(data->env__);
		rl_clear_history();
	}
}

void	safe_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_string_array(char **string_array)
{
	int	index;

	index = 0;
	if (string_array)
	{
		while (string_array[index])
		{
			if (string_array[index])
			{
				safe_free(string_array[index]);
				string_array[index] = NULL;
			}
			index++;
		}
		free(string_array);
		string_array = NULL;
	}
}
