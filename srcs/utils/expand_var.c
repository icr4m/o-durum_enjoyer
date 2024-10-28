/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:59:05 by rsk               #+#    #+#             */
/*   Updated: 2024/10/28 15:44:35 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(char *str, int start, int i, t_data *data)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_substr(str, start + 1, i - (start + 1));
	if (!var_name)
		return (NULL);
	var_value = ft_getenv_content(data, var_name);
	if (!var_value)
		var_value = "";
	return (var_value);
}

static char	*expand_var(char *str, int start, int *end, t_data *data)
{
	char	*var_value;
	char	*result;
	int		i;

	i = start + 1;
	if (!str[i] || (!is_valid_var_char(str[i]) && str[i] != '?'))
	{
		*end = start;
		return (str);
	}
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	*end = i;
	var_value = get_var_value(str, start, i, data);
	if (!var_value)
		return (NULL);
	result = ft_strjoin3(ft_substr(str, 0, start), var_value, str + *end);
	return (result);
}

static char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	if (!str)
		return (NULL);
	result = gc_malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			result = process_quotes(result, str, &i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static void	expand_single_arg(char **arg, t_data *data)
{
	int		var_end;
	char	quote;

	quote = 0;
	var_end = 0;
	while ((*arg)[var_end])
	{
		handle_quote((*arg)[var_end], &quote);
		if ((*arg)[var_end] == '$' && quote != '\'')
			*arg = expand_var(*arg, var_end, &var_end, data);
		if (*arg)
			var_end++;
	}
	*arg = remove_quotes(*arg);
}

void	expand_variables_in_node(t_ast_node *node, t_data *data)
{
	int i;

	if (!node || !node->args)
		return ;
	i = 0;
	while (node->args[i])
	{
		expand_single_arg(&node->args[i], data);
		i++;
	}
	expand_variables_in_node(node->left, data);
	expand_variables_in_node(node->right, data);
}