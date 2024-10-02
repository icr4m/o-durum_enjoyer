/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:40:40 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 10:59:59 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_env(t_data *data, char *content)
{
	size_t			i;
	t_env			*current;
	const size_t	len = ft_strlen(content);

	i = 0;
	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->env_var, content, len) == 0)
			return (current->env_var + len + 1);
		current = current->next;
	}
	return (NULL);
}
