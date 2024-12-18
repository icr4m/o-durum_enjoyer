/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:46:09 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/29 19:13:45 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp, t_data *data)
{
	t_env	*env_list;
	t_env	*new_node;
	t_env	*last_node;
	int		i;

	env_list = NULL;
	last_node = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = gc_malloc(sizeof(t_env));
		if (!new_node)
			handle_malloc_error("int env", data);
		new_node->env_var = ft_strdup(envp[i]);
		if (!new_node->env_var)
			handle_malloc_error("int env", data);
		new_node->next = NULL;
		if (!env_list)
			env_list = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
		i++;
	}
	return (env_list);
}

t_env	*search_in_env(t_data *data, const char *name)
{
	t_env	*current;
	size_t	name_len;

	if (!data || !name)
		return (NULL);
	name_len = ft_strlen(name);
	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->env_var, name, name_len) == 0
			&& current->env_var[name_len] == '=')
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

char	*ft_getenv_content(t_data *data, char *var_name)
{
	t_env	*current;
	size_t	name_len;

	current = data->env;
	if (!current)
		return (NULL);
	name_len = ft_strlen(var_name);
	while (current)
	{
		if (ft_strncmp(var_name, current->env_var, ft_strlen(var_name)) == 0
			&& current->env_var[name_len] == '=')
			break ;
		current = current->next;
	}
	if (!current)
		return (NULL);
	return (current->env_var + ft_strlen(var_name) + 1);
}

char	*ft_getenv_total(t_data *data, char *var_name)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(var_name, current->env_var, ft_strlen(var_name)) == 0)
			break ;
		current = current->next;
	}
	if (!current)
		return (NULL);
	return (current->env_var);
}
