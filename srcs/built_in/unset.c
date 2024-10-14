/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:08:19 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/14 15:02:26 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_env **env, t_env *prev, t_env *current)
{
	if (prev)
		prev->next = current->next;
	else
		*env = current->next;
	gc_free(current->env_var);
	gc_free(current);
}

int	ft_unset(t_data *data, char **args)
{
	t_env	*current;
	t_env	*prev;
	int		i;
	size_t	len;

	i = 1;
	while (args[i] != NULL)
	{
		prev = NULL;
		current = data->env;
		len = ft_strlen(args[i]);
		while (current)
		{
			if (ft_strncmp(args[i], current->env_var, len) == 0)
			{
				remove_env_var(&(data->env), prev, current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	return (0);
}
