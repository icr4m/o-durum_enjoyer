/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:19:59 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/19 22:24:58 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	*gc_malloc(long int size)
{
	static t_garbage	*garbage;
	void				*ptr;

	if (!garbage && size != DESTROY_TOKEN)
		garbage = init_garbage();
	if (size == DESTROY_TOKEN)
	{
		garbage = NULL;
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	push_to_garbage(garbage, ptr);
	if (!garbage->total_alloc)
		gc_free(garbage);
	garbage->total_alloc++;
	return (ptr);
}

void	gc_free(void *ptr)
{
	static int			i = DESTROY_TOKEN;
	static t_garbage	*garbage;

	if (ptr == DESTROY_PTR)
	{
		i = DESTROY_TOKEN;
		destroy_all(garbage);
		garbage = gc_malloc(DESTROY_TOKEN);
		return ;
	}
	if (!ptr)
		return ;
	if (i == DESTROY_TOKEN)
	{
		garbage = ptr;
		i++;
		return ;
	}
	destroy(garbage, ptr);
	garbage->total_free++;
}
