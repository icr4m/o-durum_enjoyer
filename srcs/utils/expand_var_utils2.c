/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:21:40 by erwfonta          #+#    #+#             */
/*   Updated: 2024/11/12 19:10:12 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quotes(char *str, int start, int *end)
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

static char	*handle_char_progression(char *result, int *i, char *quote,
		t_data *data)
{
	char	*old_result;
	size_t	len;

	len = ft_strlen(result);
	if (*i >= (int)len || !result[*i])
		return (result);
	if ((result[*i] == '\'' || result[*i] == '\"') && !*quote)
		*quote = result[*i];
	else if ((result[*i] == '\'' || result[*i] == '\"') && *quote == result[*i])
		*quote = 0;
	else if (result[*i] == '$' && *quote != '\'')
	{
		old_result = result;
		result = expand_single_var(result, *i, i, data);
		gc_free(old_result);
		if (!result)
			return (NULL);
		return (result);
	}
	(*i)++;
	return (result);
}

char	*process_string(char *str, t_data *data)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (1)
	{
		result = handle_char_progression(result, &i, &quote, data);
		if (!result || !result[i])
			break ;
	}
	return (result);
}
