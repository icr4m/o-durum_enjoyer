/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 04:31:24 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 04:55:09 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_data *data)
{
	(void)data;
	gc_free(DESTROY_PTR);
	rl_clear_history();
	exit(EXIT_FAILURE);
}
