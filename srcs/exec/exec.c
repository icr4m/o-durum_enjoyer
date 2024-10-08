/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:22:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 14:27:42 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast(t_ast_node *node, t_data *data)
{
	if (node == NULL)
		return ;
	else if (node->type == TOKEN_PIPE)
		pipe_exec(node, data);
	else if (node->type == TOKEN_REDIR_IN)
		handle_redirection_in(node, data);
	else if (node->type == TOKEN_REDIR_HEREDOC)
		handle_heredoc_in(node, data);
	else if (node->type == TOKEN_REDIR_OUT)
		handle_redirection_out(node, data);
	else if (node->type == TOKEN_REDIR_APPEND)
		handle_heredoc_out(node, data);
	// else if (node->type == TOKEN_ENV_VAR)
	// 	exec_env_var(node->args, data);
	else if (node->type == TOKEN_WORD)
		exec_command(node, data);
}
