/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:36:36 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 19:00:07 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**realloc_env(t_shell_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env__[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env__[i]);
		safe_free(data->env__[i]);
		i++;
	}
	free(data->env__);
	return (new_env);
}

static bool	update_delete_env_var(t_shell_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env__))
		return (false);
	safe_free(data->env__[idx]);
	i = idx;
	count = idx;
	while (data->env__[i + 1])
	{
		data->env__[i] = ft_strdup(data->env__[i + 1]);
		safe_free(data->env__[i + 1]);
		count++;
		i++;
	}
	data->env__ = realloc_env(data, count);
	if (!data->env__)
		return (false);
	return (true);
}

int	unset_builtin_cmd(t_shell_data *data, char **args)
{
	int	i;
	int	x;
	int	r;

	r = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '='))
		{
			errmsg_cmd("unset", args[i], "invalid identifier", false);
			r = 1;
		}
		else
		{
			x = get_env_var_index(data->env__, args[i]);
			if (x != -1)
				update_delete_env_var(data, x);
		}
		i++;
	}
	return (r);
}
