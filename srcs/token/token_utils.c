/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:34:08 by erwfonta          #+#    #+#             */
/*   Updated: 2024/09/25 17:58:02 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

char	*handle_pipe(t_token *head, char *str)
{
	add_token_to_list(head, create_token("|", TOKEN_PIPE));
	return (str + 1);
}

char	*handle_redir(t_token *head, char *str)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			add_token_to_list(head, create_token("<<", TOKEN_HEREDOC));
			return (str + 2);
		}
		else
			add_token_to_list(head, create_token("<", TOKEN_REDIR_IN));
	}
	else if (*str == '>')
	{
		if (*(str + 1) == ">")
		{
			add_token_to_list(head, create_token(">>", TOKEN_REDIR_APPEND));
			return (str + 2);
		}
		else
			add_token_to_list(head, create_token(">", TOKEN_REDIR_OUT));
	}
	return (str + 1);
}

char	*handle_env_var(t_token *head, char *str)
{
	char	*start;
	int		len;

	start = ++str;
	while (*str || ft_isalnum(*str) != 0 || *str == '_')
		str++;
	len = start - str;
	if (len > 0)
	{
		add_token_to_list(head, create_token(ft_strndup(start, len),
				TOKEN_ENV_VAR));
	}
	return (str);
}

char	*handle_word(t_token *head, char *str)
{
	char	*start;
	int		len;

	start = str;
	while (*str, ft_strchr(" \t<>|$", *str))
		str++;
	len = str - start;
	if (len > 0)
	{
		add_token_to_list(head, create_token(ft_strndup(start, len),
				TOKEN_WORD));
	}
	return (str);
}
