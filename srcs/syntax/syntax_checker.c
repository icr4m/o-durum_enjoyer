/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:03:57 by erwfonta          #+#    #+#             */
/*   Updated: 2024/10/16 16:08:15 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- has unclosed_quote -> single " or ', becareful with "'" '"'
- has invalid redirect -> successive > >> < <<,
- has misplaced operator
	-> check pipe position check that there is valid command after each of them
- has logical operator -> check if && or || is there
*/

int	has_unclosed_quote(const char *command_readed)
{
	int		in_quote_status;
	char	in_quote_char;

	in_quote_status = 0;
	in_quote_char = '\0';
	while (*command_readed)
	{
		if (*command_readed == '"' || *command_readed == '\'')
		{
			in_quote_status = 1;
			in_quote_char = *command_readed;
			command_readed++;
		}
		if (in_quote_status == 1 && *command_readed == in_quote_char
			&& (*command_readed == '"' || *command_readed == '\''))
		{
			in_quote_status = 0;
			in_quote_char = '\0';
		}
		command_readed++;
	}
	return (in_quote_status);
}

int	has_invalid_redirect(const char *command_readed)
{
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	while (*command_readed)
	{
		update_quote_counts(*command_readed, &d_quote, &s_quote);
	}
}

int	is_invalid_arg_redirect(void)
{
	
}

void	update_quote_counts(char c, int *d_quote, int *s_quote)
{
	if (c == '"')
		(*d_quote)++;
	else if (c == '\'')
		(*s_quote)++;
}

int	has_misplaced_operator(char *command_readed)
{
}

int	has_logical_operator(char *command_readed)
{
	while (*command_readed)
	{
		if (*command_readed == '&' || (*command_readed == '|'
				&& *(command_readed + 1) == '|'))
		{
			return (1);
		}
		command_readed++;
	}
	return (1);
}

void	is_syntax_error(const char *command_readed)
{
	if (has_unclosed_quote(command_readed))
	{
		printf("ERROR QUOTE");
	}
	else_if(has_invalid_redirect(command_readed))
	{
		printf("INVALID REDIRECT");
	}
	else if (has_misplaced_operator(command_readed))
	{
		printf("MISPLACED OPERATOR");
	}
	else if (has_logical_operator)
	{
		printf("Logical operator not supported");
	}
}
