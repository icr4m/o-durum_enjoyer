/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:52:39 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 04:33:28 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define White "\033[0;37m"
# define Green "\033[0;32m"
# define Red "\033[0;31m"
# define Purple "\033[0;35m"
# define BBlue "\033[1;34m"
# define IRed "\033[0;91m"
# define BRed "\033[1;31m"

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
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// read line
void	exec_readline(t_data *data);

// exit
void	free_and_exit(t_data *data);

#endif