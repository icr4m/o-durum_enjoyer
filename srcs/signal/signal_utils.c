/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:46:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/16 15:41:53 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	g_signal_received = 128 + signum;
	write(1, "\n", 1);
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_parent(int num)
{
	g_signal_received = num + 128;
}

void	check_if_signal(t_data *data)
{
	if (g_signal_received == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (data->status_code == 128 + SIGSEGV)
		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
	g_signal_received = 0;
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = 1;
		write(STDOUT_FILENO, "\n", 1);
	}
}
