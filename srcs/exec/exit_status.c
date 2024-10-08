/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:59:26 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 11:00:10 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(int status, t_data *data)
{
	if (WIFSIGNALED(status))
		data->status_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		data->status_code = WEXITSTATUS(status);
	else if (WIFSTOPPED(status))
		data->status_code = 128 + WSTOPSIG(status);
}
