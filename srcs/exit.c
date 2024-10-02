/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 04:31:24 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 15:27:33 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_malloc_error(char *message, t_data *data)
{
	printf("minishell: Error gc_malloc when allocate for %s\n", message);
	data->status_code = EXIT_FAILURE;
	free_and_exit(data->status_code);
}

void	free_and_exit(int code)
{
	gc_free(DESTROY_PTR);
	rl_clear_history();
	exit(code);
}
