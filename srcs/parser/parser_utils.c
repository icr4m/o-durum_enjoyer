/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:40:14 by rsk               #+#    #+#             */
/*   Updated: 2024/10/04 16:32:44 by erwfonta         ###   ########.fr       */
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
	t_ast_node	*redirect_node;

	redirect_node = create_ast_node((*token)->type);
	*token = (*token)->next->next;
	redirect_node->left = parse_redirection(token);
}

void	fill_cmd_args(t_token **token, int arg_count, t_ast_node *cmd_node)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (i < arg_count)
	{
		cmd_node->args[i] = ft_strdup((*token)->value);
		tmp = (*token);
		*token = (*token)->next;
		free(tmp->value);
		free(tmp);
		i++;
	}
	cmd_node->args[i] = NULL;
}

int	count_cmd_args(t_token **token)
{
	int	arg_count;

	arg_count = 0;
	while ((*token)->value)
	{
		arg_count++;
		*token = (*token)->next;
	}
	return (arg_count);
}
