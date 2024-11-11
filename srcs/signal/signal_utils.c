/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:46:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 17:38:28 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_event(void)
{
	return (0);
}

void	sigint_handler(int signum)
{
	g_signal_received = 128 + signum;
	rl_done = 1;
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	set_info_signal(t_data *data)
{
	data->status_code = g_signal_received;
	g_signal_received = 0;
}

void	check_if_signal(void)
{
	if (g_signal_received == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (g_signal_received == 128 + SIGINT)
		write(STDERR_FILENO, "\n", 1);
	g_signal_received = 0;
}
