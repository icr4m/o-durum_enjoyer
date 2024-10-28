/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:59:05 by rsk               #+#    #+#             */
/*   Updated: 2024/10/28 18:13:30 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:59:05 by erwfonta          #+#    #+#             */
/*   Updated: 2024/10/28 18:06:35 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_var_end(char *str, int start)
{
	int	i;

	i = start;
	if (str[i] == '?')
		return (i + 1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*get_var_name(char *str, int start, int end)
{
	return (ft_substr(str, start, end - start));
}

static char	*expand_single_var(char *str, int start, int *end, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	char	*prefix;
	char	*suffix;

	if (str[start + 1] == '\0' || str[start + 1] == '\"' || str[start
		+ 1] == '\'')
	{
		*end = start + 1;
		return (ft_strdup(str));
	}
	*end = find_var_end(str, start + 1);
	if (str[start + 1] == '?')
	{
		var_value = ft_itoa(data->status_code);
		prefix = ft_substr(str, 0, start);
		suffix = ft_strdup(str + *end);
		result = ft_strjoin3(prefix, var_value, suffix);
		return (result);
	}
	var_name = get_var_name(str, start + 1, *end);
	var_value = ft_getenv_content(data, var_name);
	if (!var_value)
		var_value = "";
	prefix = ft_substr(str, 0, start);
	suffix = ft_strdup(str + *end);
	result = ft_strjoin3(prefix, var_value, suffix);
	return (result);
}

static char	*process_string(char *str, t_data *data)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	result = ft_strdup(str);
	while (result && result[i])
	{
		if ((result[i] == '\'' || result[i] == '\"') && !quote)
			quote = result[i];
		else if ((result[i] == '\'' || result[i] == '\"') && quote == result[i])
			quote = 0;
		else if (result[i] == '$' && quote != '\'')
		{
			result = expand_single_var(result, i, &i, data);
			if (!result)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (result);
}

void	expand_variables_in_node(t_ast_node *node, t_data *data)
{
	int i;
	char *expanded;
	char *unquoted;

	if (!node || !node->args)
		return ;
	i = 0;
	while (node->args[i])
	{
		expanded = process_string(node->args[i], data);
		if (expanded)
		{
			unquoted = remove_quotes(expanded);
			if (unquoted)
				node->args[i] = unquoted;
		}
		i++;
	}
	expand_variables_in_node(node->left, data);
	expand_variables_in_node(node->right, data);
}