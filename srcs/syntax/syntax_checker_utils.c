/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:04:09 by erwfonta          #+#    #+#             */
/*   Updated: 2024/10/15 15:10:01 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	update_quote_counts(char c, int *d_quote, int *s_quote)
{
	if (c == '"')
		(*d_quote)++;
	else if (c == '\'')
		(*s_quote)++;
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
	return (0);
}