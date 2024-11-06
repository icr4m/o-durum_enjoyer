/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:59:05 by rsk               #+#    #+#             */
/*   Updated: 2024/11/06 16:31:21 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_quotes(char *str, int start, int *end)
{
	char	*prefix;
	char	*suffix;
	char	*result;

	if (str[start + 1] != '\"' && str[start + 1] != '\'')
		return (NULL);
	prefix = ft_substr(str, 0, start);
	suffix = ft_strdup(str + start + 1);
	result = ft_strjoin(prefix, suffix);
	*end = start + ft_strlen(result);
	return (result);
}

static char	*handle_var_expansion(char *str, int start, int end, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*prefix;
	char	*suffix;
	char	*result;

	var_name = get_var_name(str, start + 1, end);
	var_value = ft_getenv_content(data, var_name);
	if (!var_value)
		var_value = "";
	prefix = ft_substr(str, 0, start);
	suffix = ft_strdup(str + end);
	result = ft_strjoin3(prefix, var_value, suffix);
	return (result);
}

static char	*expand_single_var(char *str, int start, int *end, t_data *data)
{
	char	*result;

	result = handle_empty_or_null(str, start, end);
	if (result)
		return (result);
	*end = find_var_end(str, start + 1);
	result = handle_question_mark(str, start, end, data);
	if (result)
		return (result);
	result = handle_quotes(str, start, end);
	if (result)
		return (result);
	return (handle_var_expansion(str, start, *end, data));
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
	int		i;
	char	*expanded;
	char	*unquoted;

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
