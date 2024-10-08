/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:33:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/06 22:53:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_temp_filename(t_data *data)
{
	static int	count = 0;
	char		*filename;
	char		*temp_dir;

	temp_dir = search_in_env(data, "TMPDIR");
	if (!temp_dir)
		temp_dir = "/tmp";
	filename = ft_strjoin3(temp_dir, "/minishell_heredoc_", ft_itoa(count));
	count++;
	return (filename);
}

int	create_heredoc(char *delimiter, t_data *data)
{
	char	*filename;
	int		fd;
	char	*line;

	filename = get_temp_filename(data);
	if (!filename)
		return (-1);
	fd = ft_open_infile(filename, data, O_APPEND);
	if (fd == -1)
	{
		free(filename);
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (fd);
}

void	handle_heredoc(t_ast_node *node, t_data *data)
{
	int	here_doc_fd;

	here_doc_fd = create_heredoc(node[1], data);
}
