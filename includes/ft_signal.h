/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:04:37 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 11:04:59 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include "minishell.h"

// signal handler
void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	setup_sig_handler(void);
void	setup_sig_parent(void);

#endif