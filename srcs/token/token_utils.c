/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:34:08 by erwfonta          #+#    #+#             */
/*   Updated: 2024/10/08 18:09:44 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

char	*handle_pipe(t_token **head, char *str)
{
	add_token_to_list(head, create_token("|", TOKEN_PIPE));
	return (str + 1);
}

char	*handle_redir(t_token **head, char *str)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			add_token_to_list(head, create_token("<<", TOKEN_REDIR_HEREDOC));
			return (str + 2);
		}
		else
			add_token_to_list(head, create_token("<", TOKEN_REDIR_IN));
	}
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
		{
			add_token_to_list(head, create_token(">>", TOKEN_REDIR_APPEND));
			return (str + 2);
		}
		else
			add_token_to_list(head, create_token(">", TOKEN_REDIR_OUT));
	}
	return (str + 1);
}

char	*handle_word(t_token **head, char *str)
{
	char	*start;
	int		len;
	int		in_quote;
	char	quote_char;

	in_quote = 0;
	quote_char = 0;
	start = str;
	while (*str)
	{
		quote_status(*str, &in_quote, &quote_char);
		if (!in_quote && ft_strchr(" \t<>|$", *str))
			break ;
		str++;
	}
	len = str - start;
	if (len > 0)
		add_token_to_list(head, create_token(ft_strndup(start, len),
				TOKEN_WORD));
	return (str);
}

void	quote_status(char c, int *in_quote, char *quote_char)
{
	if (*in_quote && c == *quote_char)
	{
		*in_quote = 0;
		*quote_char = 0;
	}
	else if (!*in_quote && (c == '\'' || c == '\"'))
	{
		*in_quote = 1;
		*quote_char = c;
	}
}
