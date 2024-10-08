/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:48 by erwfonta          #+#    #+#             */
/*   Updated: 2024/10/08 18:09:38 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (len < n && s1[len])
		len++;
	dup = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*handle_quoted_var(t_token **head, char *str, char quote)
{
	char	*end;

	end = ft_strchr(str + 1, quote);
	if (!end)
		end = str + ft_strlen(str);
	add_token_to_list(head, create_token(ft_strndup(str + 1, end - str - 1),
			TOKEN_WORD));
	if (*end)
		return (end + 1);
	return (end);
}

char	*handle_env_var(t_token **head, char *str)
{
	char	*start;
	int		len;

	if (!*(str + 1))
	{
		add_token_to_list(head, create_token(ft_strdup("$"), TOKEN_WORD));
		return (str + 1);
	}
	if (*(str + 1) == '\'' || *(str + 1) == '\"')
		return (handle_quoted_var(head, str + 1, *(str + 1)));
	start = str + 1;
	while (*start && (ft_isalnum(*start) || *start == '_'))
		start++;
	len = start - (str + 1);
	if (len == 0)
	{
		add_token_to_list(head, create_token(ft_strdup("$"), TOKEN_WORD));
		return (str + 1);
	}
	add_token_to_list(head, create_token(ft_strndup(str, len + 1), TOKEN_WORD));
	return (start);
}
