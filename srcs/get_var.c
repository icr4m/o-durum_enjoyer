/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 02:46:44 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/22 21:36:10 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], "USER", 4) == 0)
		{
			if (data->envp[i][4] == '=')
				return (data->envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

static char	*extract_before_dot(char *input)
{
	const char	*dot_position = strchr(input, '.');
	size_t		length;
	char		*result;

	if (dot_position == NULL)
		return (input);
	length = dot_position - input;
	result = (char *)malloc(length + 1);
	if (result == NULL)
		return (NULL);
	strncpy(result, input, length);
	result[length] = '\0';
	return (result);
}

char	*get_station(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->envp[i] != NULL)
	{
		j = 0;
		if (ft_strncmp(data->envp[i], "SESSION_MANAGER", 15) == 0)
		{
			while (data->envp[i][j])
			{
				if (data->envp[i][j] == '/')
					return (extract_before_dot(data->envp[i] + j + 1));
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
