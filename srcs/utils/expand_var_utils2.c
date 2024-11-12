/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:21:40 by erwfonta          #+#    #+#             */
/*   Updated: 2024/11/12 16:39:39 by erwfonta         ###   ########.fr       */
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

char	*expand_single_var(char *str, int start, int *end, t_data *data)
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
