/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:57:00 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 16:57:24 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_output_redirection(int fd, t_data *data)
{
	if (data->backup_stdout == -42)
	{
		data->backup_stdout = dup(STDOUT_FILENO);
		if (data->backup_stdout == -1)
		{
			ft_close(fd);
			return (-1);
		}
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_close(fd);
		if (data->is_child)
			free_and_exit(-1);
		return (-1);
	}
	ft_close(fd);
	return (0);
}

static void	restore_output(t_data *data)
{
	if (data->backup_stdout != -42)
	{
		dup2(data->backup_stdout, STDOUT_FILENO);
		ft_close(data->backup_stdout);
		data->backup_stdout = -42;
	}
}

static int	process_outfile(t_ast_node *current, t_data *data)
{
	int		fd;
	char	*filename;

	filename = current->right->args[0];
	if (current->type == TOKEN_REDIR_OUT)
		fd = ft_open_outfile(filename, O_TRUNC, data);
	else
		fd = ft_open_outfile(filename, O_APPEND, data);
	if (fd == -1)
		return (-1);
	return (setup_output_redirection(fd, data));
}

int	handle_multiple_redirections(t_ast_node *node, t_data *data)
{
	t_ast_node	*current;

	current = node;
	while (current && (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND))
	{
		if (process_outfile(current, data) == -1)
			return (-1);
		current = current->left;
	}
	if (current)
		execute_ast(current, data);
	restore_output(data);
	return (0);
}
