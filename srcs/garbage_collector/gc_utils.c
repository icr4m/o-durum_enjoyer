/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:25:13 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/19 23:26:15 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

/**
 * push_to_garbage
	- Ajoute un nouvel objet à la liste des objets gérés par le garbage collector.
 * @garbage: Un pointeur vers la structure du garbage collector.
 * @ptr: Un pointeur vers l'objet à ajouter.
 *

	* Alloue de la mémoire pour une nouvelle structure t_to_destroy et
	l'ajoute à la fin de la liste des objets gérés.
 * Retourne un pointeur vers la nouvelle structure t_to_destroy,
	ou NULL en cas d'échec d'allocation.
 */

t_to_destroy	*push_to_garbage(t_garbage *garbage, void *ptr)
{
	t_to_destroy	*new;
	t_to_destroy	*current;

	new = malloc(sizeof(t_to_destroy));
	if (!new)
		return (NULL);
	new->ptr_destroy = ptr;
	new->before = NULL;
	if (!garbage->first)
		garbage->first = new;
	else
	{
		current = garbage->first;
		while (current->next)
			current = current->next;
		current->next = new;
		new->before = current;
	}
	new->next = NULL;
	return (new);
}

/**
 * is_in_garbage - Vérifie si un objet est géré par le garbage collector.
 * @garbage: Un pointeur vers la structure du garbage collector.
 * @content: Un pointeur vers l'objet à vérifier.
 *
 * Parcourt la liste des objets gérés pour vérifier si l'objet est présent.
 * Retourne 1 si l'objet est trouvé, 0 sinon.
 */

int	is_in_garbage(t_garbage *garbage, void *content)
{
	t_to_destroy	*current;

	current = garbage->first;
	while (current)
	{
		if (current->ptr_destroy == content)
			return (1);
		current = current->next;
	}
	return (0);
}
