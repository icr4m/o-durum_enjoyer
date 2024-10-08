/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 18:24:39 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_readline(t_data *data)
// {
// 	char	*command_readed;
// 	char	*prompt;
// 	char	*full_prompt;

// 	(void)data;
// 	while (1)
// 	{
// 		setup_sig_parent();
// 		if (g_signal_received != 0)
// 		{
// 			g_signal_received = 0;
// 			continue ;
// 		}
// 		prompt = getcwd(NULL, 0);
// 		full_prompt = ft_strjoin3(BBLUE "→ ", prompt,
// 				BRED " minishell> " WHITE);
// 		gc_free(prompt);
// 		command_readed = readline(full_prompt);
// 		gc_free(full_prompt);
// 		if (command_readed == NULL)
// 			break ;
// 		if (ft_strlen(command_readed) > 0)
// 			add_history(command_readed);
// 		gc_free(command_readed);
// 	}
// }

#include "minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[] = {"WORD", "PIPE", "REDIRECT_IN",
			"REDIRECT_OUT", "REDIRECT_APPEND", "REDIRECT_HEREDOC",
			"TOKEN_ENV_VAR"};

	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	display_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		printf("Token: \033[0;36m%-20s \033[0m |\t Type: \033[0;35m%-18s \033[0m \n",
			token->value, get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		token = token->next;
	}
}

void	display_ast(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");
	printf("%s", get_token_type_name(node->type));
	if (node->args)
	{
		printf(" (");
		for (int i = 0; node->args[i]; i++)
		{
			printf("%s", node->args[i]);
			if (node->args[i + 1])
				printf(", ");
		}
		printf(")");
	}
	printf("\n");
	display_ast(node->left, depth + 1);
	display_ast(node->right, depth + 1);
}

void	exec_readline(void)
{
	char		*command_readed;
	char		*prompt;
	char		*full_prompt;
	t_token		*tokens;
	t_ast_node	*ast_root;

	while (1)
	{
		setup_sig_parent();
		if (g_signal_received != 0)
		{
			g_signal_received = 0;
			continue ;
		}
		prompt = getcwd(NULL, 0);
		full_prompt = ft_strjoin3(BBLUE "→ ", prompt,
				BRED " minishell> " WHITE);
		gc_free(prompt);
		command_readed = readline(full_prompt);
		gc_free(full_prompt);
		if (command_readed == NULL)
			break ;
		if (ft_strlen(command_readed) > 0)
		{
			add_history(command_readed);
			printf("\nInput: %s\n", command_readed);
			tokens = tokenization_input(command_readed);
			printf("Tokens:\n");
			display_tokens(tokens);
			printf("nous y etes");
			ast_root = parse_tokens(&tokens);
			printf("\n");
		}
		gc_free(command_readed);
	}
}
