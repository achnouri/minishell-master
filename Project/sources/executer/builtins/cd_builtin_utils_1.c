/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:01:46 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 18:10:05 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	update_set_env_var(t_shell_data *data, char *key_var, char *var_val)
{
	int		env_index;
	char	*tmp_join;

	env_index = get_env_var_index(data->env__, key_var);
	if (!var_val)
		var_val = "";
	tmp_join = ft_strjoin("=", var_val);
	if (!tmp_join)
		return (false);
	if (env_index != -1 && data->env__[env_index])
	{
		safe_free(data->env__[env_index]);
		data->env__[env_index] = ft_strjoin(key_var, tmp_join);
	}
	else
	{
		env_index = env_var_count(data->env__);
		data->env__ = realloc_env(data, env_index + 1);
		if (!data->env__)
			return (false);
		data->env__[env_index] = ft_strjoin(key_var, tmp_join);
	}
	safe_free(tmp_join);
	return (true);
}

void	update_env_path(t_shell_data *data, char *cur_dir)
{
	update_set_env_var(data, "OLDPWD",
		get_env_var_value(data->env__, "PWD"));
	update_set_env_var(data, "PWD", cur_dir);
	if (data->old_dir)
	{
		safe_free(data->old_dir);
		data->old_dir = ft_strdup(data->current_dir);
	}
	if (data->current_dir)
	{
		safe_free(data->current_dir);
		data->current_dir = ft_strdup(cur_dir);
	}
	safe_free(cur_dir);
}

bool	can_access_dir(const char *path)
{
	return (access(path, X_OK) == 0);
}

char	*get_dotdot_path(t_shell_data *data)
{
	char	*last_slash;

	last_slash = ft_strrchr(data->current_dir, '/');
	if (!last_slash)
		return (NULL);
	if (last_slash == data->current_dir)
		return (ft_strdup("/"));
	return (ft_strndup(data->current_dir,
			last_slash - data->current_dir));
}

char	*get_other_path(t_shell_data *data, char *path)
{
	char	*joined;
	char	*new_path;

	joined = ft_strjoin(data->current_dir, "/");
	new_path = NULL;
	if (joined)
	{
		new_path = ft_strjoin(joined, path);
		safe_free(joined);
	}
	return (new_path);
}
