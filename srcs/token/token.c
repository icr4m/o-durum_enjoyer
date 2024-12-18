/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsk <rsk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:33:58 by erwfonta          #+#    #+#             */
/*   Updated: 2024/10/24 14:47:36 by rsk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenization_input(char *input)
{
	t_token	*head;
	char	*current;

	head = NULL;
	current = input;
	while (*current)
	{
		current = skip_spaces(current);
		if (*current == '|')
			current = handle_pipe(&head, current);
		else if (*current == '>' || *current == '<')
			current = handle_redir(&head, current);
		else if (*current)
			current = handle_word(&head, current);
	}
	return (head);
}
