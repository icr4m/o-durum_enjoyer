/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:04:09 by erwfonta          #+#    #+#             */
/*   Updated: 2024/11/12 14:40:59 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	update_quote_counts(char c, int *d_quote, int *s_quote)
{
	if (c == '"')
		(*d_quote)++;
	else if (c == '\'')
		(*s_quote)++;
}

char	has_logical_operator(char *command_readed)
{
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	while (*command_readed)
	{
		update_quote_counts(*command_readed, &d_quote, &s_quote);
		if (!(d_quote % 2) && !(s_quote % 2))
		{
			if (*command_readed == '&')
				return ('&');
			if (*command_readed == '|' && *(command_readed + 1) == '|')
				return ('|');
		}
		command_readed++;
	}
	return (0);
}

int	has_unclosed_quote(char *command_readed)
{
	int		in_quote_status;
	char	in_quote_char;

	in_quote_status = 0;
	in_quote_char = '\0';
	while (*command_readed)
	{
		if ((*command_readed == '"' || *command_readed == '\'')
			&& !in_quote_status)
		{
			in_quote_status = 1;
			in_quote_char = *command_readed;
		}
		else if (in_quote_status && *command_readed == in_quote_char)
		{
			in_quote_status = 0;
			in_quote_char = '\0';
		}
		command_readed++;
	}
	return (in_quote_status);
}
