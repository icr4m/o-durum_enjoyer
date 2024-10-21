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

int	has_unclosed_quote(char *command_readed)
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

int	is_invalid_arg_redirect(char *input)
{
	char	*start;

	start = input;
	input++;
	if (start == input)
		input++;
	input = skip_spaces(input);
	if (*input == '\0' || *input == '|' || *input == '>' || *input == '<')
		return (1);
	return (0);
}

int	has_invalid_redirect(char *command_readed)
{
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	while (*command_readed)
	{
		update_quote_counts(*command_readed, &d_quote, &s_quote);
		if (!(d_quote % 2) && !(s_quote % 2) && ((*command_readed == '<')
				|| (*command_readed == '>')))
			if (is_invalid_arg_redirect(command_readed))
			{
				return (1);
			}
		command_readed++;
	}
	return (0);
}

int	has_misplaced_operator(char *command_readed)
{
	int	expect_next;
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	expect_next = 0;
	if (*command_readed == '|')
		return (1);
	while (*command_readed)
	{
		update_quote_counts(*command_readed, &d_quote, &s_quote);
		if (*command_readed == '|' && !(s_quote % 2) && !(d_quote % 2))
		{
			if (expect_next)
				return (1);
			expect_next = 1;
		}
		else if (!ft_isspace(*command_readed))
			expect_next = 0;
		command_readed++;
	}
	if (expect_next)
		return (1);
	return (0);
}

void	is_syntax_error(char *command_readed)
{
	if (has_unclosed_quote(command_readed))
	{
		printf("ERROR QUOTE");
	}
	else if (has_invalid_redirect(command_readed))
	{
		printf("INVALID REDIRECT");
	}
	else if (has_misplaced_operator(command_readed))
	{
		printf("MISPLACED OPERATOR");
	}
	else if (has_logical_operator(command_readed))
	{
		printf("Logical operator not supported");
	}
}
