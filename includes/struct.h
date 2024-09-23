/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:51:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 11:39:53 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "minishell.h"

typedef enum s_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT,
	NODE_AND,
	NODE_OR
}						t_node_type;

/**
 * @brief Structure representing a command.
 * @details Used to store command information.
 * @param name Name of the command.
 * @param args Arguments of the command.
 */
typedef struct s_command
{
	char				*name;
	char				**args;
}						t_command;

/**
 * @brief Structure representing a redirection.
 * @details Used to store redirection information.
 * @param file Redirection file.
 * @param type Type of redirection.
 */
typedef struct s_redirect
{
	char				*file;
	int					type;
}						t_redirect;

/**
 * @brief Structure representing a node in the binary tree.
 * @details Used to store information about a node in the binary tree.
 * @param command Pointer to a command structure.
 * @param redirect Pointer to a redirection structure.
 * @param left Pointer to the left node of the binary tree.
 * @param right Pointer to the right node of the binary tree.
 */
typedef struct s_ast_node
{
	struct s_command	*command;
	struct s_redirect	*redirect;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_token
{
	int					lenght;
	t_node_type			type;
	char				*value;
}						t_token;

typedef struct s_data
{
	t_ast_node			*b_tree;
	t_garbage			*gc;
	char				**envp;
	int					status_code;
}						t_data;

#endif