/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:46:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/25 18:53:17 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data *data, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = gc_malloc(sizeof(char **) * (i + 1));
	if (!data->env)
		gc_free(DESTROY_PTR);
	i = 0;
	while (envp[i])
	{
		data->env[i] = envp[i];
		i++;
	}
	data->env[i] = NULL;
}
