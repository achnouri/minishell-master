/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_initialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:21:23 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:21:23 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_var_index(char **env__, char *var)
{
	int		index;
	char	*search_key;

	search_key = ft_strjoin(var, "=");
	if (!search_key)
		return (-1);
	index = 0;
	while (env__[index])
	{
		if (ft_strncmp(search_key, env__[index],
				ft_strlen(search_key)) == 0)
		{
			safe_free(search_key);
			return (index);
		}
		index++;
	}
	safe_free(search_key);
	return (-1);
}

static bool	init_path_current_and_old_dir(t_shell_data *data)
{
	char	buffer[PATH_MAX];
	char	*cwd_res;

	cwd_res = getcwd(buffer, PATH_MAX);
	if (!cwd_res)
		return (false);
	data->current_dir = ft_strdup(cwd_res);
	if (!data->current_dir)
		return (false);
	if (get_env_var_index(data->env__, "OLDPWD") != -1)
	{
		data->old_dir = ft_strdup(get_env_var_value(data->env__, "OLDPWD"));
		if (!data->old_dir)
			return (false);
	}
	else
	{
		data->old_dir = ft_strdup(cwd_res);
		if (!data->old_dir)
			return (false);
	}
	return (true);
}

static bool	copy_env(t_shell_data *data, char **env)
{
	int	i;

	i = 0;
	data->env__ = ft_calloc(env_var_count(env) + 1, sizeof(char *));
	if (!data->env__)
		return (false);
	while (env[i])
	{
		data->env__[i] = ft_strdup(env[i]);
		if (!data->env__[i])
			return (false);
		i++;
	}
	update_shlvl(data);
	return (true);
}

static bool	init_env(t_shell_data *data, char **env)
{
	char	buffer[PATH_MAX];
	char	*cwd;

	if (!env || !env[0])
	{
		cwd = getcwd(buffer, PATH_MAX);
		if (!cwd)
			return (false);
		return (init_minimal_env(data, cwd));
	}
	return (copy_env(data, env));
}

bool	init_data(t_shell_data *shell_data, char **env)
{
	if (!init_env(shell_data, env))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_path_current_and_old_dir(shell_data))
	{
		errmsg_cmd("Fatal", NULL,
			"Could not initialize working directories", 1);
		return (false);
	}
	shell_data->token = NULL;
	shell_data->line_input = NULL;
	shell_data->cmd = NULL;
	shell_data->pid = -1;
	shell_data->exit_status = 0;
	return (true);
}
