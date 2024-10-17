/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:19:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/17 15:03:37 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_list(t_env *env_list)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env_list, t_data *data)
{
	t_env	*current;
	char	**env_array;
	int		i;

	env_array = (char **)gc_malloc(sizeof(char *) * (count_env_list(env_list)
				+ 1));
	if (!env_array)
		handle_malloc_error("env", data);
	current = env_list;
	i = 0;
	while (current)
	{
		env_array[i] = ft_strdup(current->env_var);
		if (!env_array[i])
		{
			while (i > 0)
				gc_free(env_array[--i]);
			gc_free(env_array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
