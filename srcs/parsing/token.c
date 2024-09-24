/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:42:36 by erwfonta          #+#    #+#             */
/*   Updated: 2024/09/24 15:19:55 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = gc_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->lenght = ft_strlen(value);
	new_token->next = NULL;
	return (new_token);
}

t_token	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token	*parse_input(char *input)
{
	t_token	*head;
	char	*current;
	char	*start;
	int		len;
	char	*word;
	int		i;

	head = NULL;
	current = input;
	i = 0;
	while (*current)
	{
		while (current == ' ')
			current++;
		if (current == '|')
		{
			add_token_to_list(&head, TOKEN_PIPE);
			current++;
		}
		else if (*current == '<')
		{
			add_token(&head, create_token("<", TOKEN_REDIR_APPEND));
			current++;
		}
		else if (*current == '>')
		{
			add_token(&head, create_token(">", TOKEN_REDIR_OUT));
			current++;
		}
		else
		{
			start = current;
			while (*current && *current != ' ' && *current != '|'
				&& *current != '<' && *current != '>')
				current++;
			len = current - start;
			word = malloc(len + 1);
			if (!word)
				return (NULL);
			while (i < len)
			{
				word[i] = start[i];
				i++;
			}
			word[len] = '\0';
			add_token(&head, create_token(word, TOKEN_WORD));
		}
	}
	return (head);
}
