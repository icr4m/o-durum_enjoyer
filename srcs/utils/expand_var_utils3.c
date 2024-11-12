/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:51:30 by erwfonta          #+#    #+#             */
/*   Updated: 2024/11/12 17:09:34 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	handle_quotes(char current_char, char quote)
{
	if ((current_char == '\'' || current_char == '\"') && !quote)
		return (current_char);
	else if ((current_char == '\'' || current_char == '\"')
			&& quote == current_char)
		return (0);
	return (quote);
}

static char	*init_result(const char *str, int *i,char *quote)
{
	*i = 0;
	*quote = 0;
	if (!str)
		return (NULL);
	return (ft_strdup(str));
}

static char	*handle_expansion(char *result, int *i, t_data *data)
{
	char	*old_result;

	old_result = result;
	result = expand_single_var(result, *i, i, data);
	gc_free(old_result);
	return (result);
}

char	*process_string(char *str, t_data *data)
{
	int		i;
	char	quote;
	char	*result;
	size_t	len;

	result = init_result(str, &i, &quote);
	if (!result)
		return (NULL);
	while (1)
	{
		len = ft_strlen(result);
		if (i >= (int)len || !result[i])
			break ;
		quote = handle_quotes(result[i], quote);
		if (result[i] == '$' && quote != '\'')
		{
			result = handle_expansion(result, &i, data);
			if (!result)
				return (NULL);
			i = 0;
			continue ;
		}
		i++;
	}
	return (result);
}
