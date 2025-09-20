/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:27:17 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 21:12:25 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_valid_env_var_key(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (false);
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
	{
		if (!is_valid_var_char(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static char	*find_valid_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			errmsg_cmd("malloc", NULL, "an unexpected error occured",
				EXIT_FAILURE);
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		safe_free(cmd_path);
		i++;
	}
	return (NULL);
}

static char	**get_paths_from_env(t_shell_data *data)
{
	char	**env_paths;

	if (get_env_var_index(data->env__, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(get_env_var_value(data->env__, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

char	*get_cmd_path(t_shell_data *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_paths_from_env(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_string_array(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	if (!cmd_path)
	{
		safe_free(cmd);
		free_string_array(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
