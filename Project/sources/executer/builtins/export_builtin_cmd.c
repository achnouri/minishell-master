/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:36:27 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/23 23:15:37 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_exported_env(char **env)
{
	int		i;
	char	*equal_sign;
	int		key_len;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			key_len = equal_sign - env[i];
			write(1, env[i], key_len);
			write(1, "=\"", 2);
			ft_putstr_fd(equal_sign + 1, 1);
			write(1, "\"\n", 2);
		}
		else
			ft_putendl_fd(env[i], 1);
		i++;
	}
}

static char	**parse_env_var_value(char *arg, bool *append_mode)
{
	char	**tmp;
	char	*pos;

	*append_mode = false;
	tmp = ft_malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	pos = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (pos)
	{
		*append_mode = true;
		tmp[0] = ft_substr(arg, 0, pos - arg);
		tmp[1] = ft_strdup(pos + 2);
	}
	else
	{
		pos = ft_strchr(arg, '=');
		tmp[0] = ft_substr(arg, 0, pos - arg);
		tmp[1] = ft_strdup(pos + 1);
	}
	tmp[2] = NULL;
	return (tmp);
}

void	append_env_var(t_shell_data *data, char *key, char *append_val)
{
	char	*old_val;
	char	*new_val;

	old_val = get_env_var_value(data->env__, key);
	if (old_val)
		new_val = ft_strjoin(old_val, append_val);
	else
		new_val = ft_strdup(append_val);
	if (!new_val)
	{
		errmsg_cmd("export", key, "memory error", false);
		return ;
	}
	update_set_env_var(data, key, new_val);
	free(new_val);
}

static int	process_export_arg(t_shell_data *data, char *arg)
{
	char	**tmp;
	bool	append_mode;

	if (!is_valid_env_var_key(arg))
	{
		errmsg_cmd("export", arg, "invalid identifier", false);
		return (EXIT_FAILURE);
	}
	if (ft_strchr(arg, '='))
	{
		tmp = parse_env_var_value(arg, &append_mode);
		if (!tmp || !tmp[0])
		{
			errmsg_cmd("export", arg, "memory error", false);
			return (free_string_array(tmp), EXIT_FAILURE);
		}
		if (append_mode)
			append_env_var(data, tmp[0], tmp[1]);
		else
			update_set_env_var(data, tmp[0], tmp[1]);
		free_string_array(tmp);
	}
	else if (!get_env_var_value(data->env__, arg))
		update_set_env_var(data, arg, NULL);
	return (0);
}

int	export_builtin_cmd(t_shell_data *data, char **args)
{
	int	i;
	int	r;
	int	res;

	i = 1;
	r = 0;
	if (!args[i])
	{
		print_exported_env(data->env__);
		return (0);
	}
	while (args[i])
	{
		res = process_export_arg(data, args[i]);
		if (res == EXIT_FAILURE)
			r = EXIT_FAILURE;
		i++;
	}
	return (r);
}
