/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gb_coll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achnouri <achnouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:33:49 by achnouri          #+#    #+#             */
/*   Updated: 2025/07/24 00:39:36 by achnouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	t_malloc	*last(t_malloc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static	void	ft_lstadd_back_malloc(t_malloc **lst, t_malloc *new)
{
	t_malloc	*tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = last(*lst);
	if (tmp)
		tmp->next = new;
}

static	t_malloc	**root(void)
{
	static t_malloc	*ptr;

	return (&ptr);
}

void	free_malloc_list(int status)
{
	t_malloc	**head;
	t_malloc	*current;
	t_malloc	*next_node;

	head = root();
	if (!head || !*head)
		exit(2);
	current = *head;
	while (current)
	{
		next_node = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next_node;
	}
	*head = NULL;
	rl_clear_history();
	exit(status);
}

void	*ft_malloc(size_t size)
{
	t_malloc	*node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
		free_malloc_list(2);
	node = malloc(sizeof(t_malloc));
	if (!node)
	{
		free(ptr);
		free_malloc_list(2);
	}
	node->ptr = ptr;
	node->next = NULL;
	ft_lstadd_back_malloc(root(), node);
	return (ptr);
}
