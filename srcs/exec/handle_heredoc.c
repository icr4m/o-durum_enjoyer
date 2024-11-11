/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:33:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 17:04:29 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_temp_filename(t_data *data)
{
	static int	count = 0;
	char		*filename;
	char		*temp_dir;

	temp_dir = ft_getenv_content(data, "TMPDIR");
	if (!temp_dir)
		temp_dir = "/tmp";
	filename = ft_strjoin3(temp_dir, "/minishell_heredoc_", ft_itoa(count));
	count++;
	return (filename);
}

static int	read_heredoc_content(int fd, const char *real_delimiter,
		char *delimiter)
{
	static size_t	count_line = 1;
	char			*line;

	while (1)
	{
		setup_heredoc_signals();
		ft_fprintf(STDERR_FILENO, "heredoc> ");
		line = get_next_line(0);
		if (!line || strcmp(line, real_delimiter) == 0 || g_signal_received)
		{
			if (!line && !g_signal_received)
				ft_fprintf(2, "\nminishell: warning: here-document at line \
%d delimited by end-of-file (wanted `%s')\n", count_line, delimiter);
			return (0);
		}
		write(fd, line, strlen(line));
		count_line++;
	}
	return (0);
}

int	create_heredoc(char *delimiter, t_data *data)
{
	const char	*real_delimiter;
	char		*filename;
	int			fd;

	real_delimiter = ft_strjoin(delimiter, "\n");
	filename = get_temp_filename(data);
	if (!real_delimiter)
		handle_malloc_error("heredoc", data);
	if (!filename)
		return (-1);
	fd = ft_open_outfile(filename, O_APPEND, data);
	if (fd == -1)
		return (-1);
	read_heredoc_content(fd, real_delimiter, delimiter);
	ft_close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	return (fd);
}

void	check_here_doc(t_ast_node *node, t_data *data)
{
	int	fd;

	if (node == NULL)
		return ;
	if (g_signal_received)
		return ;
	if (node->type == TOKEN_REDIR_HEREDOC)
	{
		fd = create_heredoc(node->right->args[0], data);
		if (fd == -1)
			free_and_exit(-1);
		node->heredoc_fd = fd;
	}
	if (g_signal_received)
		close_heredocs(data->root);
	check_here_doc(node->left, data);
	check_here_doc(node->right, data);
}

void	execute_heredoc_redirection(t_ast_node *node, t_data *data)
{
	int	old_stdin;

	if (data->backup_stdin == -42)
	{
		old_stdin = dup(STDIN_FILENO);
		if (old_stdin == -1)
		{
			ft_fprintf(2, "minishell: Error when trying to dup stdin\n");
			return ;
		}
		data->backup_stdin = old_stdin;
	}
	if (dup2(node->heredoc_fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error when trying to dup2\n");
		ft_close(node->heredoc_fd);
		if (data->is_child == 1)
			free_and_exit(-1);
		return ;
	}
	ft_close(node->heredoc_fd);
	execute_ast(node->left, data);
}
