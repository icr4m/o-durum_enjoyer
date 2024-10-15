/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:21:20 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/15 15:55:19 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_directory(t_ast_node *node)
{
	int			stat_int;
	struct stat	sa;

	stat_int = stat(node->args[0], &sa);
	if (stat_int == 0 && S_ISDIR(sa.st_mode))
	{
		ft_fprintf(2, "minishell: %s: Is a directory\n", node->args[0]);
		free_and_exit(126);
	}
	if (!ft_access_stat(node->args[0]))
		return ;
	if (errno == EACCES)
	{
		ft_fprintf(2, "minshell: %s: Permission denied\n", node->args[0]);
		free_and_exit(126);
	}
	ft_fprintf(2, "minishell: %s: No such file or directory\n", node->args[0]);
	free_and_exit(127);
}

void	exec_command_other(t_ast_node *node, t_data *data)
{
	char	*path;
	char	**envp;
	pid_t	pid;
	int		status;

	pid = ft_fork(data);
	if (pid == 0)
	{
		if (ft_strchr(node->args[0], '/'))
			check_directory(node);
		envp = env_list_to_array(data->env);
		path = find_path(node->args[0], data);
		if (!path)
		{
			ft_fprintf(2, "minishell: %s: command not found\n", node->args[0]);
			free_and_exit(127);
		}
		if (data->backup_stdout != -42)
			close(data->backup_stdout);
		if (data->backup_stdin != -42)
			close(data->backup_stdin);
		execve(path, node->args, envp);
	}
	(waitpid(pid, &status, 0), exit_status(status, data));
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
