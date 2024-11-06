/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:21:40 by erwfonta          #+#    #+#             */
/*   Updated: 2024/11/06 18:22:40 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quotes(char *str, int start, int *end)
{
	char *prefix;
	char *suffix;
	char *result;

	if (str[start + 1] != '\"' && str[start + 1] != '\'')
		return (NULL);
	prefix = ft_substr(str, 0, start);
	suffix = ft_strdup(str + start + 1);
	result = ft_strjoin(prefix, suffix);
	*end = start + ft_strlen(result);
	return (result);
}