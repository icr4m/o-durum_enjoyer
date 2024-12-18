/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:40:14 by rsk               #+#    #+#             */
/*   Updated: 2024/11/06 18:27:32 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_token_type type)
{
	t_ast_node	*node;

	node = gc_malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->heredoc_fd = -1;
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*create_and_link_redirection(t_token **tokens, t_token *tmp)
{
	t_ast_node	*redirect_node;

	redirect_node = create_ast_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redirect_node->left = parse_redirection(tokens);
	redirect_node->right = create_file_node(tmp->next);
	return (redirect_node);
}

int	count_cmd_args(t_token *token)
{
	int	arg_count;

	arg_count = 0;
	while (token && token->type == TOKEN_WORD)
	{
		arg_count++;
		token = token->next;
	}
	return (arg_count);
}

void	fill_cmd_args(t_ast_node *cmd_node, t_token **token, int arg_count)
{
	int	i;

	i = 0;
	while (i < arg_count && *token)
	{
		cmd_node->args[i] = ft_strdup((*token)->value);
		if (!cmd_node->args[i])
		{
			while (i > 0)
				gc_free(cmd_node->args[--i]);
			gc_free(cmd_node->args);
			cmd_node->args = NULL;
			return ;
		}
		*token = (*token)->next;
		i++;
	}
	cmd_node->args[i] = NULL;
}
