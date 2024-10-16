/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:32:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/16 16:15:30 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection_in(t_ast_node *node, t_data *data)
{
	int		fd;
	char	*filename;

	filename = node->right->args[0];
	fd = ft_open_infile(filename, O_RDONLY, data);
	if (fd == -1)
		return (-1);
	data->backup_stdin = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error when trying to dup2\n");
		(ft_close(fd), ft_close(data->backup_stdin));
		if (data->is_child == 1)
			free_and_exit(-1);
		return (0);
	}
	ft_close(fd);
	execute_ast(node->left, data);
	dup2(data->backup_stdin, STDIN_FILENO);
	ft_close(data->backup_stdin);
	return (0);
}

int	handle_redirection_out(t_ast_node *node, t_data *data)
{
	int		fd;
	char	*filename;

	filename = node->right->args[0];
	fd = ft_open_outfile(filename, O_TRUNC, data);
	if (fd == -1)
		return (-1);
	data->backup_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error when trying to dup2\n");
		(ft_close(fd), ft_close(data->backup_stdout));
		if (data->is_child == 1)
			free_and_exit(-1);
		return (0);
	}
	ft_close(fd);
	execute_ast(node->left, data);
	dup2(data->backup_stdout, STDOUT_FILENO);
	ft_close(data->backup_stdout);
	return (0);
}
