/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:01:26 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 18:01:28 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	change_path(t_shell_data *data, char *path)
{
	char	cur_dir[PATH_MAX];
	char	*new_path;

	new_path = NULL;
	if (!can_access_dir(".") && ft_strncmp(path, "..", 3) == 0)
		return (handle_cd_dotdot_case(data, path));
	if (chdir(path) != 0)
	{
		errmsg_cmd("cd", path, strerror(errno), errno);
		return (false);
	}
	if (getcwd(cur_dir, PATH_MAX))
		new_path = ft_strdup(cur_dir);
	else
		new_path = handle_getcwd_failure(data, path);
	if (!new_path)
		return (false);
	update_env_path(data, new_path);
	return (true);
}

static int	handle_home_case(t_shell_data *data)
{
	char	*path;

	path = get_env_var_value(data->env__, "HOME");
	if (!path || ft_isspace(*path) || *path == '\0')
		return (errmsg_cmd("cd", NULL,
				"HOME variable is not defined or not exist", 1));
	return (change_path(data, path));
}

static int	handle_oldpwd_case(t_shell_data *data)
{
	char	*path;

	path = get_env_var_value(data->env__, "OLDPWD");
	if (!path)
		return (errmsg_cmd("cd", NULL,
				"OLDPWD variable is not defined or not exist", 1));
	return (!change_path(data, path));
}

int	cd_builtin_cmd(t_shell_data *data, char **args)
{
	if (!args || !args[1] || args[1][0] == '\0'
		|| ft_isspace(args[1][0]) || ft_strncmp(args[1], "--", 3) == 0)
		return (handle_home_case(data));
	if (args[2])
		return (errmsg_cmd("cd", NULL,
				"extra arguments are not allowed", 1));
	if (ft_strncmp(args[1], "-", 2) == 0)
		return (handle_oldpwd_case(data));
	return (!change_path(data, args[1]));
}
