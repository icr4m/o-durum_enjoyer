/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:26:02 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/19 23:08:08 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

/**
 * destroy - Libère un objet spécifique géré par le garbage collector.
 * @garbage: Un pointeur vers la structure du garbage collector.
 * @content: Un pointeur vers l'objet à libérer.
 *
 * Si l'objet n'est pas trouvé dans la liste des objets gérés,
	il est simplement libéré.
 * Sinon, il est retiré de la liste et libéré.
 */

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

/**
 * destroy_all - Libère tous les objets gérés par le garbage collector.
 * @garbage: Un pointeur vers la structure du garbage collector.
 *
 * Parcourt la liste des objets gérés et les libère tous,
	ainsi que la structure du garbage collector elle-même.
 */

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
