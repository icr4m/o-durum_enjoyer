/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:00:07 by rsk               #+#    #+#             */
/*   Updated: 2024/11/06 16:31:30 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	result = gc_malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	find_var_end(char *str, int start)
{
	int	i;

	i = start;
	if (str[i] == '?')
		return (i + 1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_var_name(char *str, int start, int end)
{
	return (ft_substr(str, start, end - start));
}

char	*handle_empty_or_null(char *str, int start, int *end)
{
	if (str[start + 1] == '\0')
	{
		*end = start + 1;
		return (ft_strdup(str));
	}
	return (NULL);
}

char	*handle_question_mark(char *str, int start, int *end, t_data *data)
{
	char	*var_value;
	char	*prefix;
	char	*suffix;
	char	*result;

	if (str[start + 1] != '?')
		return (NULL);
	var_value = ft_itoa(data->status_code);
	prefix = ft_substr(str, 0, start);
	suffix = ft_strdup(str + *end);
	result = ft_strjoin3(prefix, var_value, suffix);
	return (result);
}
