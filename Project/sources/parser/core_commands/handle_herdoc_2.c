/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 01:30:25 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/22 18:06:18 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	str = NULL;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			safe_free(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			safe_free(tmp);
		}
	}
	free_string_array(tab);
	return (str);
}

static char	*get_expanded_var_line(t_shell_data *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expander_heredoc(data, words[i]);
			if (!words[i])
			{
				free_string_array(words);
				return (NULL);
			}
		}
		i++;
	}
	return (make_str_from_tab(words));
}

static bool	evaluate_heredoc_line(t_shell_data *data, char **line,
	t_redirect *io, bool *ret)
{
	if (*line == NULL)
	{
		errmsg_cmd("warning",
			"here-document delimited by end-of-file: wanted",
			io->break_delimiter, true);
		*ret = true;
		return (false);
	}
	if (ft_strcmp(*line, io->break_delimiter) == 0)
	{
		*ret = true;
		return (false);
	}
	if (io->has_quotes == false && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(data, *line);
		if (!(*line))
		{
			*ret = false;
			return (false);
		}
	}
	return (true);
}

static bool	handle_no_line(int *delims_left)
{
	if (--(*delims_left) > 0)
		return (true);
	return (false);
}

bool	fill_heredoc(t_shell_data *data, t_redirect *io, int fd,
		int *delims_left)
{
	char	*line;
	bool	ret;

	ret = true;
	while (*delims_left > 0)
	{
		line = readline("> ");
		if (!line)
		{
			if (handle_no_line(delims_left))
				continue ;
			break ;
		}
		if (ft_strcmp(line, io->break_delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (!evaluate_heredoc_line(data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (ret);
}
