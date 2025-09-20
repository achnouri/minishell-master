/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_initialization_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerriyag <eerriyag@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-25 11:21:17 by eerriyag          #+#    #+#             */
/*   Updated: 2025-07-25 11:21:17 by eerriyag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	init_minimal_env(t_shell_data *data, char *cwd)
{
	data->env__ = ft_calloc(5, sizeof(char *));
	if (!data->env__)
		return (false);
	data->env__[0] = ft_strjoin("PWD=", cwd);
	data->env__[1] = ft_strdup("SHLVL=1");
	data->env__[2] = ft_strdup("_=/usr/bin/env");
	data->env__[3] = ft_strdup(
			"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (!data->env__[0] || !data->env__[1]
		|| !data->env__[2] || !data->env__[3])
		return (false);
	return (true);
}

void	update_shlvl(t_shell_data *data)
{
	int		idx;
	int		new_lvl;
	char	*lvl_str;
	char	*shlvl_entry;

	idx = get_env_var_index(data->env__, "SHLVL");
	if (idx == -1)
	{
		add_env_var(data, "SHLVL=1");
		return ;
	}
	new_lvl = ft_atoi(ft_strchr(data->env__[idx], '=') + 1) + 1;
	lvl_str = ft_itoa(new_lvl);
	shlvl_entry = ft_strjoin("SHLVL=", lvl_str);
	free(data->env__[idx]);
	data->env__[idx] = shlvl_entry;
	safe_free(lvl_str);
}

bool	add_env_var(t_shell_data *data, char *new_var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (data->env__ && data->env__[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (false);
	j = 0;
	while (j < i)
	{
		new_env[j] = data->env__[j];
		j++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(data->env__);
	data->env__ = new_env;
	return (true);
}

char	*get_env_var_value(char **env, char *key)
{
	int		index;
	char	*key_with_equal;

	key_with_equal = ft_strjoin(key, "=");
	if (!key_with_equal)
		return (NULL);
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(key_with_equal, env[index],
				ft_strlen(key_with_equal)) == 0)
		{
			safe_free(key_with_equal);
			return (ft_strchr(env[index], '=') + 1);
		}
		index++;
	}
	safe_free(key_with_equal);
	return (NULL);
}

bool	fih_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}
