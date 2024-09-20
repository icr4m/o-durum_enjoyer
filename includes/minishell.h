/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:52:39 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/20 03:43:24 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/libft.h"
# include "garbage_collector.h"
# include "lexing.h"
# include "struct.h"
//
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Get user
char	*get_user(t_data *data);

// get pwd
void	exec_readline(t_data *data);

#endif