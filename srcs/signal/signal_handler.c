/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 06:45:56 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 10:13:00 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	set_signal_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void	set_signal_parent_exec(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_signal_parent;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sb, 0, sizeof(sb));
	sb.sa_handler = handle_signal_parent;
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}

void	set_signal_parent(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
