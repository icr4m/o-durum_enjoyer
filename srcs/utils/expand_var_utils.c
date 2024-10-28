/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:00:07 by rsk               #+#    #+#             */
/*   Updated: 2024/10/27 11:00:51 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*process_quotes(char *result, char *str, int *i, int *j)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		result[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i])
		(*i)++;
	return (result);
}

void	handle_quote(char c, char *quote)
{
	if (c == '\'' && !*quote)
		*quote = '\'';
	else if (c == '\"' && !*quote)
		*quote = '\"';
	else if (c == *quote)
		*quote = 0;
}
