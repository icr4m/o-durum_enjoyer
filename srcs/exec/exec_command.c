/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:21:20 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/06 18:23:41 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command_other(t_ast_node *node, t_data *data)
{
	char	*path;
	char	**envp;

	envp = env_list_to_array(data->env);
	path = find_path(node->args[0], data);
	if (!path)
	{
		ft_fprintf(2, "minishell: command not found:\n", node->args[0]);
		free_and_exit(127);
	}
	execve(path, node->args, envp);
	ft_fprintf(2, "%s: Permission denied\n", node->args[0]);
	free_and_exit(126);
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
