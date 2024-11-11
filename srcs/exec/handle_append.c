/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:03:35 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 12:07:56 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_out(t_ast_node *node, t_data *data)
{
	int	here_doc_fd;

	here_doc_fd = ft_open_outfile(node->right->args[0], O_APPEND, data);
	if (here_doc_fd == -1)
		free_and_exit(-1);
	data->backup_stdout = dup(STDOUT_FILENO);
	if (dup2(here_doc_fd, STDOUT_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error when trying to dup2\n");
		(ft_close(here_doc_fd), ft_close(data->backup_stdout));
		if (data->is_child == 1)
			free_and_exit(-1);
		return (0);
	}
	ft_close(here_doc_fd);
	execute_ast(node->left, data);
	dup2(data->backup_stdout, STDOUT_FILENO);
	ft_close(data->backup_stdout);
	return (0);
}
