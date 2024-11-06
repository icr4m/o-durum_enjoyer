void	check_directory(t_ast_node *node)
{
	struct stat	sa;

	if (stat(node->args[0], &sa) == 0)
	{
		if (S_ISDIR(sa.st_mode))
		{
			ft_fprintf(2, "minishell: %s: Is a directory\n", node->args[0]);
			free_and_exit(126);
		}
		if (!(sa.st_mode & S_IXUSR))
		{
			ft_fprintf(2, "minishell: %s: Permission denied\n", node->args[0]);
			free_and_exit(126);
		}
	}
	else
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n",
			node->args[0]);
		free_and_exit(127);
	}
}

void	exec_command_other(t_ast_node *node, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

	pid = ft_fork(data);
	if (pid == 0)
	{
		envp = env_list_to_array(data->env, data);
		if (ft_strchr(node->args[0], '/'))
		{
			check_directory(node);
			path = node->args[0];
		}
		else
		{
			path = find_path(node->args[0], data);
			if (!path)
			{
				ft_fprintf(2, "minishell: %s: command not found\n",
					node->args[0]);
				free_and_exit(127);
			}
		}
		if (data->backup_stdout != -42)
			close(data->backup_stdout);
		if (data->backup_stdin != -42)
			close(data->backup_stdin);
		execve(path, node->args, envp);
		perror("execve");
		free_and_exit(126);
	}
	waitpid(pid, &status, 0);
	exit_status(status, data);
}

void	exec_command(t_ast_node *node, t_data *data)
{
	if (strcmp(node->args[0], EXPORT_STR) == 0)
		ft_export(data, node->args);
	else if (strcmp(node->args[0], CD_STR) == 0)
		ft_cd(data, node->args);
	else if (strcmp(node->args[0], ECHO_STR) == 0)
		ft_echo(data, node->args);
	else if (strcmp(node->args[0], EXIT_STR) == 0)
		ft_exit(data, node->args);
	else if (strcmp(node->args[0], ENV_STR) == 0)
		ft_env(data, node->args);
	else if (strcmp(node->args[0], UNSET_STR) == 0)
		ft_unset(data, node->args);
	else if (strcmp(node->args[0], PWD_STR) == 0)
		ft_pwd(data, 1);
	else
		exec_command_other(node, data);
}

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

void	check_here_doc(t_ast_node *node, t_data *data)
{
	int	fd;

	if (node == NULL)
		return ;
	if (node->type == TOKEN_REDIR_HEREDOC)
	{
		fd = create_heredoc(node->right->args[0], data);
		if (fd == -1)
			free_and_exit(-1);
		node->heredoc_fd = fd;
	}
	check_here_doc(node->left, data);
	check_here_doc(node->right, data);
}

static void	execute_heredoc_redirection(t_ast_node *node, t_data *data)
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

void	execute_ast(t_ast_node *node, t_data *data)
{
	if (node == NULL)
		return ;
	else if (node->type == TOKEN_PIPE)
		pipe_exec(node, data);
	else if (node->type == TOKEN_REDIR_IN)
		handle_redirection_in(node, data);
	else if (node->type == TOKEN_REDIR_HEREDOC)
	{
		if (node->heredoc_fd != -1)
			execute_heredoc_redirection(node, data);
	}
	else if (node->type == TOKEN_REDIR_OUT)
		handle_redirection_out(node, data);
	else if (node->type == TOKEN_REDIR_APPEND)
		handle_heredoc_out(node, data);
	else if (node->type == TOKEN_WORD)
		exec_command(node, data);
	if (data->backup_stdin != -42)
	{
		dup2(data->backup_stdin, STDIN_FILENO);
		ft_close(data->backup_stdin);
		data->backup_stdin = -42;
	}
}

void	exit_status(int status, t_data *data)
{
	int	sig;

	if (WIFSIGNALED(status))
		data->status_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		data->status_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_fprintf(2, "Quit (core dumped)\n");
	}
}

int	ft_fork(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
	{
		set_signal_child();
		data->is_child = 1;
	}
	return (pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:33:10 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/30 14:45:31 by ijaber           ###   ########.fr       */
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
				ft_fprintf(2,
							"\nminishell: warning: here-document at line \
%d delimited by end-of-file (wanted `%s')\n",
							count_line,
							delimiter);
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

void	pipe_exec(t_ast_node *node, t_data *data)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		free_and_exit(data->status_code);
	pid[0] = ft_fork(data);
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(execute_ast(node->left, data), free_and_exit(data->status_code));
	}
	pid[1] = ft_fork(data);
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(execute_ast(node->right, data), free_and_exit(data->status_code));
	}
	if (node->left->heredoc_fd != -1)
	{
		ft_close(node->left->heredoc_fd);
		node->left->heredoc_fd = -1;
	}
	if (node->right->heredoc_fd != -1)
	{
		ft_close(node->right->heredoc_fd);
		node->right->heredoc_fd = -1;
	}
	(ft_close(fd[0]), ft_close(fd[1]));
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	exit_status(status, data);
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
