/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:52 by rsk               #+#    #+#             */
/*   Updated: 2024/10/07 13:33:35 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*cmd_node;
	int			arg_count;

	cmd_node = create_ast_node(TOKEN_WORD);
	if (!cmd_node)
		return (NULL);
	arg_count = count_cmd_args(*token);
	cmd_node->args = gcmalloc(sizeof(char *) * (arg_count + 1));
	if (!cmd_node->args)
	{
		free(cmd_node);
		return (NULL);
	}
	fill_cmd_args(cmd_node, token, arg_count);
	return (cmd_node);
}

t_ast_node	*create_file_node(t_token *token)
{
	t_ast_node	*node;

	node = create_ast_node(token->type);
	if (!node)
		return (NULL);
	node->args = gcmalloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = ft_strdup(token->value);
	node->args[1] = NULL;
	return (node);
}

t_ast_node	*parse_redirection(t_token **token)
{
	t_token		*tmp;
	t_ast_node	*redirect_node;

	tmp = *token;
	if ((*token)->type >= TOKEN_REDIR_IN
		&& (*token)->type <= TOKEN_REDIR_HEREDOC)
		return (create_and_link_redirection(token, tmp));
	while ((*token) && (*token)->next)
	{
		if ((*token)->next->type >= TOKEN_REDIR_IN
			&& (*token)->next->type <= TOKEN_REDIR_HEREDOC)
		{
			redirect_node = create_ast_node((*token)->next->type);
			(*token)->next = (*token)->next->next;
			redirect_node->left = parse_redirection(&tmp);
			redirect_node->right = create_file_node((*token)->next);
			return (redirect_node);
		}
		(*token) = (*token)->next;
	}
	return (parse_command(&token));
}

t_ast_node	*parse_pipe(t_token **token)
{
	t_token		*tmp;
	t_ast_node	*pipe_node;

	tmp = *token;
	if ((*token)->type == TOKEN_PIPE)
		return (create_and_link_redirection(token, tmp));
	while ((*token) && (*token)->next)
	{
		if ((*token)->next->type == TOKEN_PIPE)
		{
			pipe_node = create_ast_node((*token)->next->type);
			(*token)->next = NULL;
			pipe_node->left = parse_redirection(&tmp);
			pipe_node->right = parse_pipe(&((*token)->next->next));
			return (pipe_node);
		}
		(*token) = (*token)->next;
	}
	return (parse_command(&token));
}

t_ast_node	*parse_tokens(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipe(tokens));
}