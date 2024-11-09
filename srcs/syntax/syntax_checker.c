/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:03:57 by erwfonta          #+#    #+#             */
/*   Updated: 2024/11/07 17:54:11 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_invalid_arg_redirect(char *input)
{
	char	redirect_type;

	redirect_type = *input;
	if (*input == '>' && *(input + 1) == '>')
		input++;
	else if (*input == '<' && *(input + 1) == '<')
		input++;
	input++;
	while (*input && ft_isspace(*input))
		input++;
	if (!*input)
		return (redirect_type);
	if (*input == '|' || *input == '>' || *input == '<')
		return (*input);
	return (0);
}

char	has_invalid_redirect(char *command_readed)
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
			if ((*command_readed == '<' || *command_readed == '>')
				&& is_invalid_arg_redirect(command_readed))
				return (*command_readed);
		}
		command_readed++;
	}
	return (*command_readed);
}

char	has_misplaced_operator(char *command_readed)
{
	int	expect_next;
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	expect_next = 0;
	if (*command_readed == '|')
		return ('|');
	while (*command_readed)
	{
		update_quote_counts(*command_readed, &d_quote, &s_quote);
		if (*command_readed == '|' && !(s_quote % 2) && !(d_quote % 2))
		{
			if (expect_next)
				return ('|');
			expect_next = 1;
		}
		else if (!ft_isspace(*command_readed))
			expect_next = 0;
		command_readed++;
	}
	if (expect_next)
		return ('|');
	return (*command_readed);
}

int	error_handle(t_data *data, char *command_readed)
{
	if (has_invalid_redirect(command_readed))
	{
		data->status_code = 2;
		ft_fprintf(2, "minishell : syntax error near unexpected token '%c' \n",
			has_invalid_redirect(command_readed));
		return (1);
	}
	else if (has_misplaced_operator(command_readed))
	{
		data->status_code = 2;
		ft_fprintf(2, "minishell : syntax error near unexpected token '%c' \n",
			has_misplaced_operator(command_readed));
		return (1);
	}
	else if (has_logical_operator(command_readed))
	{
		data->status_code = 2;
		ft_fprintf(2, "minishell : syntax error near unexpected token '%c' \n",
			has_logical_operator(command_readed));
		return (1);
	}
	return (0);
}

int	is_syntax_error(char *command_readed, t_data *data)
{
	if (has_unclosed_quote(command_readed))
	{
		data->status_code = 2;
		ft_fprintf(2, "minishell : syntax error open quote\n");
		return (1);
	}
	else if (error_handle(data, command_readed))
		return (1);
	return (0);
}
