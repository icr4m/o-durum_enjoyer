/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:18:20 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 00:52:42 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_exec_children(t_ast_node *node, t_data *data, int *fd,
		pid_t *pid)
{
	pid[0] = ft_fork(data);
	if (pid[0] == 0)
	{
		close_heredocs(node->right);	
		dup2(fd[1], STDOUT_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(execute_ast(node->left, data), free_and_exit(data->status_code));
	}
	pid[1] = ft_fork(data);
	if (pid[1] == 0)
	{
		close_heredocs(node->left);
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

	if (pipe(fd) == -1)
		free_and_exit(data->status_code);
	pipe_exec_children(node, data, fd, pid);
	close_heredocs(data->root);
	(ft_close(fd[0]), ft_close(fd[1]));
	(waitpid(pid[0], &status, 0), waitpid(pid[1], &status, 0));
	exit_status(status, data);
}
