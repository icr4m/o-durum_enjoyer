/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/15 01:21:52 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_parsing(char *command_readed, t_data *data)
{
	t_token		*token;
	t_ast_node	*ast_root;

	(void)data;
	token = tokenization_input(command_readed);
	// display_tokens(token);
	ast_root = parse_tokens(&token);
	generate_ast_diagram(ast_root);
	execute_ast(ast_root, data);
}

void	exec_readline(t_data *data)
{
	char	*command_readed;
	char	*prompt;
	char	*full_prompt;

	while (1)
	{
		set_signal_parent();
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
			ft_exit(data, NULL);
		if (ft_strlen(command_readed) > 0)
			(add_history(command_readed), start_parsing(command_readed, data));
		gc_free(command_readed);
	}
}