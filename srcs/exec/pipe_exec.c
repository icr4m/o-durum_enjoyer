/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:18:20 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/07 21:57:32 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_ast_node *node, t_data *data)
{
	pid_t	pid;
	int		pipefd[2];
	int		original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1 || pipe(pipefd) == -1)
		handle_pipe_error("exec", data);
	pid = ft_fork(data);
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->left, data);
		exit(0);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->right, data);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		free_and_exit(0);
	}
}
