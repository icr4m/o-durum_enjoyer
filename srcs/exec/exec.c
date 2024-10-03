/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:22:14 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/03 19:14:38 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *data)
{
	exec_ast_node(data->ast_node);
}

void	execute_ast(t_ast_node *node)
{
	pid_t pid;

	int pipefd[2];
	if (node == NULL)
		return ;

	if (node->type == TOKEN_PIPE)
	{
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
	else if (node->type >= TOKEN_REDIR_IN && node->type <= TOKEN_REDIR_HEREDOC)
	{
		handle_redirection(node);
		execute_ast(node->left);
		execute_ast(node->right);
	}
	else if (node->type == TOKEN_WORD)
	{
		exec_command(node->args);
	}
}