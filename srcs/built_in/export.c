/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:39:12 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/26 17:56:55 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data, char *var_name, char *content)
{
	size_t	i;
	size_t	len_var;
	char	*new_env;

	new_env = ft_strjoin3(var_name, "=", content);
	len_var = ft_strlen(var_name);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(var_name, data->env[i], len_var) == 0)
		{
			gc_free(data->env[i]);
			data->env[i] = new_env;
			return ;
		}
		i++;
	}
	{
		data->env = realloc(data->env, sizeof(char **) * (i + 2));
		// if (!data->env)
		// 	return (NULL);
		data->env[i] = new_env;
		data->env[i + 1] = NULL;
	}
}
