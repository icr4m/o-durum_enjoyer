/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:52:39 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/12 19:12:20 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITE "\001\033[0;37m\002"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define PURPLE "\033[0;35m"
# define BBLUE "\001\033[1;34m\002"
# define IRED "\033[0;91m"
# define BRED "\001\033[1;31m\002"
# define BGREEN "\001\033[1;32m\002"
# define BPURPLE "\001\033[1;35m\002"

# define EXPORT_STR "export"
# define CD_STR "cd"
# define ECHO_STR "echo"
# define EXIT_STR "exit"
# define ENV_STR "env"
# define UNSET_STR "unset"
# define PWD_STR "pwd"

/*
une directive qui permet d'accéder à un ensemble plus large et plus moderne
 de fonctionnalités POSIX. (pour sigaction).
*/
# define _XOPEN_SOURCE 700
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
//
# include "../includes/garbage_collector.h"
# include "../includes/lexing.h"
# include "../includes/struct.h"
# include "../includes/syntax.h"
//
# include "../includes/built_in.h"
# include "../includes/exec.h"
# include "../includes/ft_signal.h"
# include "../includes/utils.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/libft.h"

// VARIABLE GLOBALE
extern volatile sig_atomic_t	g_signal_received;

#endif