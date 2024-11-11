/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:22:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 12:31:05 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredocs(t_ast_node *root)
{
	if (!root)
		return ;
	if (root->type == TOKEN_REDIR_HEREDOC)
	{
		if (root->heredoc_fd != -1)
		{
			ft_close(root->heredoc_fd);
			root->heredoc_fd = -1;
		}
	}
	close_heredocs(root->left);
	close_heredocs(root->right);
}

void	execute_ast(t_ast_node *node, t_data *data)
{
	if (node == NULL)
		return ;
	else if (node->type == TOKEN_PIPE)
		pipe_exec(node, data);
	else if (node->type == TOKEN_REDIR_IN)
		handle_redirection_in(node, data);
	else if (node->type == TOKEN_REDIR_HEREDOC)
	{
		if (node->heredoc_fd != -1)
			execute_heredoc_redirection(node, data);
	}
	else if (node->type == TOKEN_REDIR_OUT)
		handle_redirection_out(node, data);
	else if (node->type == TOKEN_REDIR_APPEND)
		handle_heredoc_out(node, data);
	else if (node->type == TOKEN_WORD)
		exec_command(node, data);
	if (data->backup_stdin != -42)
	{
		dup2(data->backup_stdin, STDIN_FILENO);
		ft_close(data->backup_stdin);
		data->backup_stdin = -42;
	}
	check_if_signal();
}
