/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:57:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/20 15:33:21 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"
# include "struct.h"

/**
 * @brief token for each possible case
 *
 * @param token_word Commandes et arguments
 * @param token_redir_out >
 * @param token_redir_in <
 * @param token_redir_append >>
 * @param token_heredoc <<
 * @param token_pipe |
 * @param token_space Espace ou tabulation
 * @param token_newline \n
 * @param token_quote_single '
 * @param token_quote_double "
 * @param token_variable $VAR
 * @param token_escape Escape character
 * @param token_and &&
 * @param token_or ||
 * @param token_semicolon ;
 * @param token_paren_open (
 * @param token_paren_close )
 * @param token_bracket_open [
 * @param token_bracket_close ]
 */
typedef enum token
{
	TOKEN_WORD,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_SPACE,
	TOKEN_NEWLINE,
	TOKEN_QUOTE_SINGLE,
	TOKEN_QUOTE_DOUBLE,
	TOKEN_VARIABLE,
	TOKEN_ESCAPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SEMICOLON,
	TOKEN_PAREN_OPEN,
	TOKEN_PAREN_CLOSE,
	TOKEN_BRACKET_OPEN,
	TOKEN_BRACKET_CLOSE
}		t_token_type;



void	exec_readline(t_data *data);

#endif