/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:57:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 18:41:05 by erwfonta         ###   ########.fr       */
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
 */
typedef enum token
{
	TOKEN_WORD,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
}		t_token_type;

// tokenization function
t_token	*create_token(char *value, t_token_type type);
t_token	add_token_to_list(t_token **head, t_token *new_token);

#endif