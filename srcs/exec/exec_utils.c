/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:47:55 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/16 16:14:38 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_infile(char *file, int flags, t_data *data)
{
	int	fd;

	fd = open(file, flags);
	if (fd == -1)
	{
		if (data->is_child == 1)
			free_and_exit(1);
		return (-1);
	}
	return (fd);
}

int	ft_open_outfile(char *file, int flags, t_data *data)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | flags, 0644);
	if (fd == -1)
	{
		if (data->is_child == 1)
			free_and_exit(1);
		return (-1);
	}
	return (fd);
}

void	ft_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			ft_fprintf(2, "Error close fd number %d\n", fd);
			free_and_exit(-1);
		}
	}
}

char	*find_path(char *command, t_data *data)
{
	int		i;
	char	*path;
	char	**split;
	char	*all_paths;

	i = 0;
	all_paths = ft_getenv_content(data, "PATH");
	if (all_paths)
	{
		split = ft_split(all_paths, ':');
		while (split[i])
		{
			path = ft_strjoin3(split[i], "/", command);
			if (ft_access_stat(path) == 0)
			{
				gc_free_2d(split);
				return (path);
			}
			gc_free(path);
			i++;
		}
		gc_free_2d(split);
	}
	return (NULL);
}

int	ft_access_stat(char *path)
{
	int			stat_int;
	struct stat	sb;

	stat_int = stat(path, &sb);
	if (stat_int == -1)
		return (-1);
	if (S_ISREG(sb.st_mode) && access(path, F_OK | X_OK) == 0)
		return (0);
	return (-1);
}
