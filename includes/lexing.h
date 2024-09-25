/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:57:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/25 17:46:49 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

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
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
}					t_token_type;

typedef struct s_token
{
	int				lenght;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

// token List
t_token				*create_token(char *value, t_token_type type);
t_token				add_token_to_list(t_token **head, t_token *new_token);

// tokenizer
t_token				tokenization_input(char *input);

// token utils
char				skip_spaces(char *str);
char				*handle_pipe(t_token *head, char *str);
char				*handle_redir(t_token *head, char *str);
char				*handle_env_var(t_token *head, char *str);
char				*handle_word(t_token *head, char *str);

#endif