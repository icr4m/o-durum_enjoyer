/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:02:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 06:14:28 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "minishell.h"

# define DESTROY_PTR ((void *)-1)
# define DESTROY_TOKEN -1

/**
 * struct s_to_destroy
	- Structure représentant un objet à détruire par le garbage collector.
 * @ptr_destroy: Un pointeur vers l'objet à détruire.
 * @next: Un pointeur vers le prochain objet à détruire dans la liste.
 * @before: Un pointeur vers l'objet précédent dans la liste.
 *

	* Cette structure est utilisée pour créer une liste chaînée d'objets gérés 
	par le garbage collector.
 */
typedef struct s_to_destroy
{
	void				*ptr_destroy;
	struct s_to_destroy	*next;
	struct s_to_destroy	*before;
}						t_to_destroy;

/**
 * struct s_garbage - Structure représentant le garbage collector.
 * @first: Un pointeur vers le premier objet à détruire dans la liste.
 * @total_alloc: Le nombre total d'objets alloués.
 * @total_free: Le nombre total d'objets libérés.
 *

	* Cette structure est utilisée pour gérer la mémoire allouée dynamiquement 
	et assurer sa libération.
 */
typedef struct s_garbage
{
	t_to_destroy		*first;
	int					total_alloc;
	int					total_free;
}						t_garbage;

// GC destroy
void					destroy(t_garbage *garbage, void *content);
void					destroy_all(t_garbage *garbage);

// GC init
t_garbage				*init_garbage(void);

// GC malloc
void					*gc_malloc(long int size);
void					gc_free(void *ptr);

// GC utils
t_to_destroy			*push_to_garbage(t_garbage *garbage, void *ptr);
int						is_in_garbage(t_garbage *garbage, void *content);

#endif