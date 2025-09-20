/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:00:51 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 18:14:42 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*handle_getcwd_failure(t_shell_data *data, char *path)
{
	char	*new_path;

	new_path = NULL;
	if (ft_strncmp(path, "..", 3) == 0)
		new_path = get_dotdot_path(data);
	else if (ft_strncmp(path, ".", 2) == 0)
		new_path = ft_strdup(data->current_dir);
	else
		new_path = get_other_path(data, path);
	if (!new_path)
		errmsg_cmd("cd", path, "failed to construct path", errno);
	return (new_path);
}

bool	handle_cd_dotdot_case(t_shell_data *data, char *path)
{
	char	*new_path;
	char	*last_slash;

	last_slash = ft_strrchr(data->current_dir, '/');
	if (!last_slash)
		return (errmsg_cmd("cd", path,
				"cannot determine parent directory", ENOENT),
			false);
	if (last_slash == data->current_dir)
		new_path = ft_strdup("/");
	else
		new_path = ft_strndup(data->current_dir,
				last_slash - data->current_dir);
	if (!new_path)
		return (errmsg_cmd("cd", path,
				"memory allocation failed", ENOMEM),
			false);
	if (chdir(new_path) != 0)
	{
		errmsg_cmd("cd", new_path, strerror(errno), errno);
		safe_free(new_path);
		return (false);
	}
	update_env_path(data, new_path);
	return (true);
}
