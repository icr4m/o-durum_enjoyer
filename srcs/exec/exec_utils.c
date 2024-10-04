/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:47:55 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/04 16:13:01 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_infile(char *file, int flags, t_data *data)
{
	int	fd;

	fd = open(file, O_RDONLY, flags);
	if (fd == -1)
	{
		if (data->is_child == 1)
			free_and_exit(1);
		return (-1);
	}
	return (fd);
}

int	ft_open_outfile(char *file, int flags, t_data *data)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT, flags);
	if (fd == -1)
	{
		if (data->is_child == 1)
			free_and_exit(1);
		return (-1);
	}
	return (fd);
}
