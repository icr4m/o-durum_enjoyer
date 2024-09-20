/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 02:46:44 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/20 03:12:18 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user(t_data *data)
{
	int	index;

	index = 0;
	while (data->envp[index] != NULL)
	{
		if (ft_strncmp(data->envp[index], "USER", 4) == 0)
		{
			if (data->envp[index][4] == '=')
				return (data->envp[index] + 5);
		}
		index++;
	}
	return (NULL);
}
