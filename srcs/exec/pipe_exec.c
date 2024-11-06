/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:18:20 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/06 16:20:26 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_exec_children(t_ast_node *node, t_data *data, int *fd,
		pid_t *pid)
{
	int	left_heredoc;
	int	right_heredoc;

	left_heredoc = node->left->heredoc_fd;
	right_heredoc = node->right->heredoc_fd;
	pid[0] = ft_fork(data);
	if (pid[0] == 0)
	{
		if (right_heredoc != -1)
			ft_close(right_heredoc);
		dup2(fd[1], STDOUT_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(execute_ast(node->left, data), free_and_exit(data->status_code));
	}
	pid[1] = ft_fork(data);
	if (pid[1] == 0)
	{
		if (left_heredoc != -1)
			ft_close(left_heredoc);
		dup2(fd[0], STDIN_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(execute_ast(node->right, data), free_and_exit(data->status_code));
	}
}

void	pipe_exec(t_ast_node *node, t_data *data)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;
	int		left_heredoc;
	int		right_heredoc;

	left_heredoc = node->left->heredoc_fd;
	right_heredoc = node->right->heredoc_fd;
	if (pipe(fd) == -1)
		free_and_exit(data->status_code);
	pipe_exec_children(node, data, fd, pid);
	if (left_heredoc != -1)
		(ft_close(left_heredoc), node->left->heredoc_fd = -1);
	if (right_heredoc != -1)
		(ft_close(right_heredoc), node->right->heredoc_fd = -1);
	(ft_close(fd[0]), ft_close(fd[1]));
	(waitpid(pid[0], &status, 0), waitpid(pid[1], &status, 0));
	exit_status(status, data);
}
