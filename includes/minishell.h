/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:52:39 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/25 19:00:42 by ijaber           ###   ########.fr       */
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

/*
une directive qui permet d'accéder à un ensemble plus large et plus moderne
 de fonctionnalités POSIX. (pour sigaction).
*/
# define _XOPEN_SOURCE 700
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//
# include "../includes/garbage_collector.h"
# include "../includes/struct.h"
//
# include "../includes/built_in.h"
# include "../includes/expand.h"
# include "../includes/ft_signal.h"
# include "../includes/lexing.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/libft.h"

// VARIABLE GLOBALE
extern volatile sig_atomic_t	g_signal_received;

// read line
void							exec_readline(t_data *data);
char							*read_input(void);
t_token							*parse_input(char *input);
// exit
void							free_and_exit(t_data *data);

#endif