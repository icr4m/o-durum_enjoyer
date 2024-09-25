/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:33:58 by erwfonta          #+#    #+#             */
/*   Updated: 2024/09/25 17:58:11 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	tokenization_input(char *input)
{
	t_token	*head;
	char	*current;

	head = NULL;
	current = input;
	while (*input)
	{
		current = skip_spaces(current);
	}
	if (*current == '|')
		current = handle_pipe(&head, input);
	else if (*current == '>' || *current == '<')
		current = handle_redir(&head, input);
	else if (*current == '$')
		current = handle_env_var(&head, input);
	else
		current = handle_word(&head, input);
}
