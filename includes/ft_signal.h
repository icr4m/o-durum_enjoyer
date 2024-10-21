/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:04:37 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/21 11:11:00 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "minishell.h"

// SIGNAL HANDLER

void	set_signal_child(void);
void	set_signal_parent(void);
void	setup_heredoc_signals(void);

// SIGNAL UTILS

void	sigint_handler(int signum);
void	handle_signal_parent(int num);
void	heredoc_signal_handler(int signum);
int		is_heredoc_interrupted(void);

#endif