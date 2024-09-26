/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:46:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/26 13:01:43 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_data *data, char **envp)
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
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (0);
		i++;
	}
	data->env[i] = NULL;
	return (1);
}
