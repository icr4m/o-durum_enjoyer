/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:32:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 17:01:20 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_input_redirection(int fd, t_data *data)
{
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
	return (0);
}

static void	restore_input(t_data *data)
{
	if (data->backup_stdin != -42)
	{
		if (dup2(data->backup_stdin, STDIN_FILENO) == -1)
			ft_fprintf(2, "minishell: Error when trying to restore stdin\n");
		ft_close(data->backup_stdin);
		data->backup_stdin = -42;
	}
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
	if (setup_input_redirection(fd, data) == -1)
		return (-1);
	execute_ast(node->left, data);
	restore_input(data);
	return (0);
}

int	handle_redirection_out(t_ast_node *node, t_data *data)
{
	return (handle_multiple_redirections(node, data));
}
