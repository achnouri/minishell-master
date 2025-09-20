/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:36:17 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/18 18:19:06 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	echo_print(char **args, int i, bool n_option)
{
	bool	printed;

	printed = false;
	if (!args[i])
	{
		if (!n_option)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
		printed = true;
	}
	if (!n_option && printed)
		ft_putchar_fd('\n', 1);
}

bool	is_n_option(char *arg)
{
	int		i;
	bool	n_option;

	i = 0;
	n_option = false;
	if (arg[i] != '-')
		return (n_option);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_option = true;
	return (n_option);
}

int	echo_builtin_cmd(char **args)
{
	int		i;
	bool	n_option;

	n_option = false;
	i = 1;
	while (args[i] && is_n_option(args[i]))
	{
		n_option = true;
		i++;
	}
	echo_print(args, i, n_option);
	return (0);
}
