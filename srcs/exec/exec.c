/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:22:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/03 22:35:19 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_ast_node *node)
{
	pid_t	pid;
	int		pipefd[2];

	handle_child();
	if (pipe(pipefd) == -1)
		handle_pipe_error("pipe failed");
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->left);
		exit(0);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->right);
	}
}

void	execute_ast(t_ast_node *node)
{
	if (node == NULL)
		return ;
	else if (node->type == TOKEN_PIPE)
		pipe_exec(node);
	else if (node->type >= TOKEN_REDIR_IN)
	{
		handle_redirection_in(node);
		execute_ast(node->right);
	}
	else if (node->type <= TOKEN_REDIR_HEREDOC)
	{
		handle_redirection_in_heredoc(node);
		execute_ast(node->right);
	}
	else if (node->type >= TOKEN_REDIR_OUT)
	{
		handle_redirection_out(node);
		execute_ast(node->right);
	}
	else if (node->type <= TOKEN_REDIR_APPEND)
	{
		handle_redirection_out_heredoc(node);
		execute_ast(node->right);
	}
	else if (node->type == TOKEN_ENV_VAR)
		exec_env_var(node->args);
	else if (node->type == TOKEN_WORD)
		exec_command(node->args);
}
