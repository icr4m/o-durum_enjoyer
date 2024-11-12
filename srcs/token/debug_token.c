/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:13:40 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/12 14:42:38 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// const char	*get_token_type_name(t_token_type type)
// {
// 	const char	*token_type_names[] = {"WORD", "PIPE", "REDIRECT_IN",
// 			"REDIRECT_OUT", "REDIRECT_APPEND", "REDIRECT_HEREDOC",
// 			"TOKEN_ENV_VAR"};

// 	if (type >= 0 && type < 7)
// 		return (token_type_names[type]);
// 	return ("UNKNOWN");
// }

// void	display_tokens(t_token *tokens)
// {
// 	t_token	*token;

// 	token = tokens;
// 	while (token)
// 	{
// 		printf("Token: \033[0;36m%-20s \033[0m
// 	|\t Type: \033[0;35m%-18s \033[0m \n",
// 			token->value, get_token_type_name(token->type));
// 		printf("--------------------------------------------------\n");
// 		token = token->next;
// 	}
// }
