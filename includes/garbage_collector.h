/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:02:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/19 22:48:55 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "minishell.h"

# define DESTROY_PTR ((void *)-1)
# define DESTROY_TOKEN -1

typedef struct s_to_destroy
{
	void				*ptr_destroy;
	struct s_to_destroy	*next;
	struct s_to_destroy	*before;
}						t_to_destroy;

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