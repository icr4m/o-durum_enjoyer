/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:03:16 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/17 15:33:02 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(t_data *data)
{
	int		shlvl;
	char	*str_shlvl;
	char	*shlvl_value;
	t_env	*current;

	current = search_in_env(data, "SHLVL");
	if (current)
		shlvl = ft_atoi(current->env_var + 6);
	else
		shlvl = 0;
	shlvl++;
	shlvl_value = ft_itoa(shlvl);
	if (!shlvl_value)
		handle_malloc_error("SHLVL", data);
	str_shlvl = ft_strjoin("SHLVL=", shlvl_value);
	if (!str_shlvl)
		handle_malloc_error("SHLVL", data);
	if (!update_existing_env(data, "SHLVL", str_shlvl))
		add_var_to_end(data, str_shlvl);
}

static void	init_pwd(t_data *data)
{
	char	*short_pwd;
	char	*acutal_pwd;

	short_pwd = ft_pwd(data, 0);
	acutal_pwd = ft_strjoin("PWD=", short_pwd);
	free(short_pwd);
	if (!update_existing_env(data, "PWD", acutal_pwd))
		add_var_to_end(data, acutal_pwd);
}

static void	init_underscore(t_data *data)
{
	char	*underscore;

	underscore = ft_strdup("_=/usr/bin/env");
	if (!update_existing_env(data, "_", underscore))
		add_var_to_end(data, underscore);
}

void	init_minishell(t_data *data, char **envp)
{
	data->status_code = 0;
	data->is_child = 0;
	data->backup_stdin = -42;
	data->backup_stdout = -42;
	data->env = init_env(envp, data);
	update_shlvl(data);
	init_pwd(data);
	init_underscore(data);
	data->ast_node = NULL;
}
