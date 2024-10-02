/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:08:19 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/01 20:32:21 by ijaber           ###   ########.fr       */
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

int	ft_unset(t_data *data, char **vars)
{
	t_env	*current;
	t_env	*prev;
	int		i;
	size_t	len;

	i = 1;
	while (vars[i] != NULL)
	{
		prev = NULL;
		current = data->env;
		len = ft_strlen(vars[i]);
		while (current)
		{
			if (ft_strncmp(vars[i], current->env_var, len) == 0
				&& (current->env_var[len] == '='))
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
