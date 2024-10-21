/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:31:44 by erwfonta          #+#    #+#             */
/*   Updated: 2024/10/15 16:03:20 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "minishell.h"
# include "struct.h"

// syntax function
void	is_syntax_error(char *command_readed);
int		has_unclosed_quote(char *command_readed);

// syntax utils
int		ft_isspace(int c);
void	update_quote_counts(char c, int *d_quote, int *s_quote);
int		has_logical_operator(char *command_readed);

#endif