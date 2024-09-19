/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:26:02 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/19 22:35:07 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	destroy(t_garbage *garbage, void *content)
{
	t_to_destroy	*current;

	if (!garbage)
		return ;
	if (!is_in_garbage(garbage, content))
	{
		free(content);
		return ;
	}
	current = garbage->first;
	while (current->ptr_destroy != content)
		current = current->next;
	if (current->before)
		current->before->next = current->next;
	else
		garbage->first = current->next;
	if (current->next)
		current->next->before = current->before;
	(free(current->ptr_destroy), free(current));
}

void	destroy_all(t_garbage *garbage)
{
	t_to_destroy	*current;
	t_to_destroy	*next;

	if (garbage)
	{
		if (!garbage->first)
		{
			free(garbage);
			return ;
		}
		current = garbage->first;
		while (current)
		{
			next = current->next;
			free(current->ptr_destroy);
			free(current);
			current = next;
		}
	}
	free(garbage);
}
