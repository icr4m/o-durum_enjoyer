/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:57:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/03 16:58:42 by ijaber           ###   ########.fr       */
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
 * @param TOKEN_REDIR_HEREDOC <<
 * @param token_pipe |
 */
typedef enum token
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}					t_token_type;

typedef struct s_token
{
	int				lenght;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_ast_node
{
	t_token_type	type;
	int				file_type;
	char			**args;
	t_ast_node		*left;
	t_ast_node		*right;
}					t_ast_node;

// tokenization function
t_token				*create_token(char *value, t_token_type type);
t_token				add_token_to_list(t_token **head, t_token *new_token);

#endif