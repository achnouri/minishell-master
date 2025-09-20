/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:51:54 by eerriyag          #+#    #+#             */
/*   Updated: 2025/07/22 00:57:03 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_first_arg(int ac, char **av)
{
	(void)av;
	if (ac != 1)
		return (ft_putendl_fd("Usage: ./minishell", 2), false);
	return (1);
}

char	*join_strings(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	safe_free(tmp);
	return (str);
}

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	empty_line(char *line_input)
{
	int	i;

	i = 0;
	while (line_input[i] && ft_isspace(line_input[i]))
		i++;
	if (i == (int)ft_strlen(line_input))
		return (1);
	return (0);
}

int	init_check_line_input(t_shell_data *data)
{
	if (!data->line_input)
		exit_builtin_cmd(data, NULL);
	else if (ft_strcmp(data->line_input, "\0") == 0)
		return (0);
	else if (empty_line(data->line_input))
		return (1);
	return (-1);
}
