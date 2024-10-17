/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:39:12 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/17 13:05:17 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_first_value(char *str, char sep, t_data *data)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = gc_malloc(sizeof(char *) * 3);
	if (!result)
		handle_malloc_error("export", data);
	while (str[i] && str[i] != sep)
		i++;
	result[0] = ft_substr(str, 0, i);
	if (str[i] == sep)
	{
		while (str[j + i + 1])
			j++;
		result[1] = gc_malloc(sizeof(char) * (j + 1));
		if (!result[1])
			handle_malloc_error("export", data);
		ft_strlcpy(result[1], &str[i + 1], i + 1);
	}
	else
		result[1] = NULL;
	result[2] = NULL;
	return (result);
}

static int	is_a_good_variable(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	update_existing_env(t_data *data, char *var_name, char *new_env)
{
	t_env	*current;
	size_t	len_var;

	if (!data || !var_name || !new_env)
		return (0);
	len_var = ft_strlen(var_name);
	current = data->env;
	while (current)
	{
		if (ft_strncmp(var_name, current->env_var, len_var) == 0)
		{
			current->env_var = ft_strdup(new_env);
			if (!current->env_var)
				handle_malloc_error("export", data);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

t_env	*add_var_to_end(t_data *data, char *content)
{
	t_env	*new_node;
	t_env	*current;

	new_node = gc_malloc(sizeof(t_env));
	if (!new_node)
		handle_malloc_error("export", data);
	new_node->env_var = ft_strdup(content);
	if (!new_node->env_var)
		handle_malloc_error("export", data);
	new_node->next = NULL;
	if (!data->env)
	{
		data->env = new_node;
		return (new_node);
	}
	current = data->env;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (new_node);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	char	**split_arg;

	i = 1;
	data->status_code = 0;
	while (args[i])
	{
		if (!is_a_good_variable(args[i]))
		{
			ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
				args[i]);
			data->status_code = 1;
		}
		else
		{
			split_arg = split_first_value(args[i], '=', data);
			if (!update_existing_env(data, split_arg[0], args[i]))
				if (!add_var_to_end(data, ft_strdup(args[i])))
					return (0);
		}
		i++;
	}
	if (i == 1)
		print_env(data, 2);
	return (data->status_code);
}
