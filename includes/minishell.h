/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:52:39 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 09:55:02 by ijaber           ###   ########.fr       */
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
//
# include "../includes/_signal.h"
# include "../includes/built_in.h"
# include "../includes/exec.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/libft.h"

// VARIABLE GLOBALE
extern volatile sig_atomic_t	g_signal_received;

// READ LINE

void							exec_readline(t_data *data);
char							*read_input(void);
t_token							*parse_input(char *input);

// EXIT

void							free_and_exit(int code);
void							handle_pipe_error(char *message, t_data *data);
void							handle_malloc_error(char *message,
									t_data *data);

// UTILS

char							**env_list_to_array(t_env *env_list);

#endif