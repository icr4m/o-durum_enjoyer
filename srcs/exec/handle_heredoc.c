/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:33:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/15 18:20:03 by ijaber           ###   ########.fr       */
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

int	create_heredoc(char *delimiter, t_data *data)
{
	const char		*real_delimiter = ft_strjoin(delimiter, "\n");
	static size_t	count_line;
	char			*filename;
	int				fd;
	char			*line;

	count_line = 1;
	filename = get_temp_filename(data);
	if (!filename)
		return (-1);
	fd = ft_open_outfile(filename, O_APPEND, data);
	if (fd == -1)
		return (-1);
	while (1)
	{
		ft_fprintf(STDERR_FILENO, "heredoc> ");
		line = get_next_line(0);
		if (!line || strcmp(line, real_delimiter) == 0)
		{
			if (!line)
				ft_fprintf(2,
							"\nminishell: warning: here-document at line \
%d delimited by end-of-file (wanted `%s')\n",
							count_line,
							delimiter);
			break ;
		}
		write(fd, line, strlen(line));
		count_line++;
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	return (fd);
}

int	handle_heredoc_in(t_ast_node *node, t_data *data)
{
	int	here_doc_fd;

	here_doc_fd = create_heredoc(node->right->args[0], data);
	if (here_doc_fd == -1)
		free_and_exit(-1);
	data->backup_stdin = dup(STDIN_FILENO);
	if (dup2(here_doc_fd, STDIN_FILENO) == -1)
	{
		ft_fprintf(2, "minishell: Error when trying to dup2\n");
		(close(here_doc_fd), close(data->backup_stdin));
		if (data->is_child == 1)
			free_and_exit(-1);
		return (0);
	}
	close(here_doc_fd);
	execute_ast(node->left, data);
	dup2(data->backup_stdin, STDIN_FILENO);
	close(data->backup_stdin);
	return (0);
}

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
		(close(here_doc_fd), close(data->backup_stdout));
		if (data->is_child == 1)
			free_and_exit(-1);
		return (0);
	}
	close(here_doc_fd);
	execute_ast(node->left, data);
	dup2(data->backup_stdout, STDOUT_FILENO);
	close(data->backup_stdout);
	return (0);
}
