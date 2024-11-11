/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:32:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 12:24:34 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_multiple_redirections(t_ast_node *node, t_data *data)
{
	int			fd;
	char		*filename;
	t_ast_node	*current;

	current = node;
	while (current && (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND))
	{
		filename = current->right->args[0];
		if (current->type == TOKEN_REDIR_OUT)
			fd = ft_open_outfile(filename, O_TRUNC, data);
		else
			fd = ft_open_outfile(filename, O_APPEND, data);
		if (fd == -1)
			return (-1);
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
		current = current->left;
	}
	if (current)
		execute_ast(current, data);
	if (data->backup_stdout != -42)
	{
		dup2(data->backup_stdout, STDOUT_FILENO);
		ft_close(data->backup_stdout);
		data->backup_stdout = -42;
	}
	return (0);
}

int	handle_redirection_in(t_ast_node *node, t_data *data)
{
	int		fd;
	char	*filename;

	filename = node->right->args[0];
	fd = ft_open_infile(filename, O_RDONLY, data);
	if (fd == -1)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", filename);
		return (-1);
	}
	if (data->backup_stdin == -42)
	{
		data->backup_stdin = dup(STDIN_FILENO);
		if (data->backup_stdin == -1)
		{
			ft_close(fd);
			ft_fprintf(2, "minishell: Error when trying to backup stdin\n");
			return (-1);
		}
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error when trying to dup2\n");
		ft_close(fd);
		return (-1);
	}
	ft_close(fd);
	execute_ast(node->left, data);
	if (data->backup_stdin != -42)
	{
		if (dup2(data->backup_stdin, STDIN_FILENO) == -1)
			ft_fprintf(2, "minishell: Error when trying to restore stdin\n");
		ft_close(data->backup_stdin);
		data->backup_stdin = -42;
	}
	return (0);
}

int	handle_redirection_out(t_ast_node *node, t_data *data)
{
	return (handle_multiple_redirections(node, data));
}
