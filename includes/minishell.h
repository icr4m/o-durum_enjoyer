/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:52:39 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 09:17:17 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITE "\033[0;37m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define PURPLE "\033[0;35m"
# define BBLUE "\033[1;34m"
# define IRED "\033[0;91m"
# define BRED "\033[1;31m"

# define _XOPEN_SOURCE 700
/*
une directive qui permet d'accéder à un ensemble plus large et plus moderne
 de fonctionnalités POSIX. (pour sigaction).
*/

# include "../includes/ft_signal.h"
# include "../includes/garbage_collector.h"
# include "../includes/lexing.h"
# include "../includes/struct.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/libft.h"
//
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// VARIABLE GLOBALE
extern volatile sig_atomic_t	g_signal_received;

// read line
void							exec_readline(t_data *data);

// exit
void							free_and_exit(t_data *data);

#endif