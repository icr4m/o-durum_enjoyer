/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:22:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/30 14:45:46 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_here_doc(t_ast_node *node, t_data *data)
{
	int	fd;

	if (node == NULL)
		return ;
	if (node->type == TOKEN_REDIR_HEREDOC)
	{
		fd = create_heredoc(node->right->args[0], data);
		if (fd == -1)
			free_and_exit(-1);
		node->heredoc_fd = fd;
	}
	check_here_doc(node->left, data);
	check_here_doc(node->right, data);
}

static void	execute_heredoc_redirection(t_ast_node *node, t_data *data)
{
	int	old_stdin;

	if (data->backup_stdin == -42)
	{
		old_stdin = dup(STDIN_FILENO);
		if (old_stdin == -1)
		{
			ft_fprintf(2, "minishell: Error when trying to dup stdin\n");
			return ;
		}
		data->backup_stdin = old_stdin;
	}
	if (dup2(node->heredoc_fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error when trying to dup2\n");
		ft_close(node->heredoc_fd);
		if (data->is_child == 1)
			free_and_exit(-1);
		return ;
	}
	ft_close(node->heredoc_fd);
	execute_ast(node->left, data);
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
}
