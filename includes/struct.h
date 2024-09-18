/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:51:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/18 23:41:57 by ijaber           ###   ########.fr       */
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

typedef struct s_command
{
	char				*name;
	char				**args;
}						t_command;

typedef struct s_redirect
{
	char				*file;
	int					type;
}						t_redirect;

typedef struct s_ast_node
{
	struct s_command	*command;
	struct s_redirect	*redirect;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

#endif