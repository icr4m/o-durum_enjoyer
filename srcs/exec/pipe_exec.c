/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:18:20 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/29 16:04:57 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_ast_node *node, t_data *data)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;
	int		heredoc_fd;

	if (pipe(fd) == -1)
		free_and_exit(data->status_code);
	heredoc_fd = node->right->heredoc_fd;
	pid[0] = ft_fork(data);
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		if (node->left->heredoc_fd != -1)
			ft_close(node->left->heredoc_fd);
		(execute_ast(node->left, data), free_and_exit(data->status_code));
	}
	pid[1] = ft_fork(data);
	if (pid[1] == 0)
	{
		if (heredoc_fd != -1)
		{
			dup2(heredoc_fd, STDIN_FILENO);
			ft_close(heredoc_fd);
		}
		else
			dup2(fd[0], STDIN_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(execute_ast(node->right, data), free_and_exit(data->status_code));
	}
	(ft_close(fd[0]), ft_close(fd[1]));
	if (heredoc_fd != -1)
		ft_close(heredoc_fd);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	exit_status(status, data);
}
