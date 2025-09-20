/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:10:29 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/22 18:08:57 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	check_line_limit_of_delimiters(char *heredoc_line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (heredoc_line[i])
	{
		if (heredoc_line[i] == '<' && heredoc_line[i + 1] == '<')
		{
			c++;
			i += 2;
			while (heredoc_line[i] == ' ' || heredoc_line[i] == '\t')
				i++;
			if (!heredoc_line[i])
				break ;
		}
		else
			i++;
	}
	if (c >= 17)
		return (false);
	return (true);
}

char	*get_delimiter(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

bool	heredoc_res(t_redirect *io, int result)
{
	if (result == 300)
	{
		io->fd_in = -1;
		return (false);
	}
	if (result == 404)
		io->fd_in = -1;
	return (true);
}
