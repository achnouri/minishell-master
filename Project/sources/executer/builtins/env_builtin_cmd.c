/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:36:20 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 18:20:37 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_builtin_cmd(t_shell_data *data, char **args)
{
	int	env_line;

	if (args && args[1])
		return (errmsg_cmd("env", NULL,
				"extra arguments are not allowed", 2));
	env_line = 0;
	if (!data->env__)
		return (1);
	while (data->env__[env_line])
		ft_putendl_fd(data->env__[env_line++], 1);
	return (1);
}
