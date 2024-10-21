/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:59:26 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 11:34:56 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(int status, t_data *data)
{
	int	sig;

	if (WIFSIGNALED(status))
		data->status_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		data->status_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_fprintf(2, "Quit (core dumped)\n");
	}
}
