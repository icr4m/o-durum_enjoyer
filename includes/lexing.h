/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:57:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/07 13:59:41 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"
# include "stddef.h"

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
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}						t_token_type;

typedef struct s_token
{
	int					lenght;
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_ast_node
{
	t_token_type		type;
	int					file_type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

// token List
t_token					*create_token(char *value, t_token_type type);
t_token					add_token_to_list(t_token **head, t_token *new_token);

// tokenizer
t_token					*tokenization_input(char *input);

// token utils
char					*skip_spaces(char *str);
char					*handle_pipe(t_token *head, char *str);
char					*handle_redir(t_token *head, char *str);
char					*handle_env_var(t_token *head, char *str);
char					*handle_word(t_token *head, char *str);
void					quote_status(char c, int *in_quote, char *quote_char);

// Parsing
t_ast_node				*parse_command(t_token **token);
t_ast_node				*create_file_node(t_token *token);
t_ast_node				*parse_redirection(t_token **token);
t_ast_node				*parse_pipe(t_token **token);
t_ast_node				*parse_tokens(t_token **tokens);

// Parser Utils
t_ast_node				*create_ast_node(t_token_type type);
t_ast_node				*create_and_link_redirection(t_token **token,
							t_token *tmp);
void					fill_cmd_args(t_token **token, int arg_count,
							t_ast_node *cmd_node);
int						count_cmd_args(t_token **token);
void					free_ast(t_ast_node *node);

#endif