/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:39:12 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/25 19:42:52 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, char *var_name, char *content)
{
	size_t	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(var_name, data->env[i], ft_strlen(var_name)) == 0)
		// && data->env[i][ft_strlen(var_name)] == '=')
		{
			printf("test1\n");
			gc_free(data->env[i]);
			data->env[i] = gc_malloc(sizeof(char *) * (ft_strlen(content) + 1));
		}
		else
		{
			printf("test2\n");
			data->env = gc_realloc(data->env, sizeof(char **) * (i + 2));
			// if (!data->env)
			// 	return (NULL);
			data->env[i] = content;
			data->env[i + 2] = NULL;
		}
		i++;
	}
}
