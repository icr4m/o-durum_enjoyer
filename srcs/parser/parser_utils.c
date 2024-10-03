/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:40:14 by rsk               #+#    #+#             */
/*   Updated: 2024/10/02 15:40:30 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_token_type type)
{
	t_ast_node	*node;

	node = gcmalloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*create_and_link_redirection(t_token **token, t_token *tmp)
{
	t_ast_node *redirect_node;

	redirect_node = new_ast_node((*token)->type);
	*token = (*token)->next->next;
	redirect_node->left = parse_redirection(token);
}