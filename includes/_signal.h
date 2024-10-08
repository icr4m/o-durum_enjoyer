/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _signal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:04:37 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 10:10:33 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"

// SIGNAL HANDLER

void	set_signal_child(void);
void	set_signal_parent(void);
void	set_signal_parent_exec(void);

// SIGNAL UTILS

void	sigint_handler(int signum);
void	handle_signal_parent(int num);

#endif