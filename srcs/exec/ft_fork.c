/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:27:49 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 09:58:47 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_and_exit(-1);
	if (pid == 0)
	{
		set_signal_child();
		data->is_child = 1;
	}
	return (pid);
}