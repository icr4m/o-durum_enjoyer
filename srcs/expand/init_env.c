/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:46:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/28 16:24:30 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	t_env	*last_node;
	int		i;

	env_list = NULL;
	last_node = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = gc_malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->env_var = ft_strdup(envp[i]);
		if (!new_node->env_var)
			return (NULL);
		new_node->next = NULL;
		if (!env_list)
			env_list = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
		i++;
	}
	return (env_list);
}
