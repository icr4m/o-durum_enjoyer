/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:52 by rsk               #+#    #+#             */
/*   Updated: 2024/11/12 14:41:37 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*cmd_node;
	int			arg_count;

	if (!token || !*token)
		return (NULL);
	cmd_node = create_ast_node(TOKEN_WORD);
	if (!cmd_node)
		return (NULL);
	arg_count = count_cmd_args(*token);
	cmd_node->args = gc_malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd_node->args)
	{
		return (NULL);
	}
	fill_cmd_args(cmd_node, token, arg_count);
	return (cmd_node);
}

t_ast_node	*create_file_node(t_token *token)
{
	t_ast_node	*node;

	node = gc_malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->args = gc_malloc(sizeof(char *) * 2);
	if (!node->args)
		return (NULL);
	node->args[0] = token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*parse_redirection(t_token **tokens)
{
	t_token		*tmp;
	t_ast_node	*redirect_node;
	t_token		*next_token;

	if (!*tokens)
		return (NULL);
	tmp = *tokens;
	if ((*tokens)->type >= TOKEN_REDIR_IN
		&& (*tokens)->type <= TOKEN_REDIR_HEREDOC)
		return (create_and_link_redirection(tokens, tmp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= TOKEN_REDIR_IN
			&& (*tokens)->next->type <= TOKEN_REDIR_HEREDOC)
		{
			redirect_node = create_ast_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = parse_redirection(&tmp);
			redirect_node->right = create_file_node((next_token->next));
			return (redirect_node);
		}
		*tokens = next_token;
	}
	return (parse_command(&tmp));
}

t_ast_node	*parse_pipe(t_token **tokens)
{
	t_token		*tmp;
	t_token		*next_token;
	t_ast_node	*pipe_node;

	tmp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == TOKEN_PIPE)
		{
			pipe_node = create_ast_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = parse_redirection(&tmp);
			pipe_node->right = parse_pipe(&(next_token->next));
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (parse_redirection(&tmp));
}

t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipe(tokens));
}
