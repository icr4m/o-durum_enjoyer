/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/06 16:33:52 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_parsing(char *command_readed, t_data *data)
{
	t_token		*token;
	t_ast_node	*ast_root;

	(void)data;
	if (is_syntax_error(command_readed, data))
	{
		return ;
	}
	token = tokenization_input(command_readed);
	// display_tokens(token);
	ast_root = parse_tokens(&token);
	expand_variables_in_node(ast_root, data);
	// generate_ast_diagram(ast_root);
	check_here_doc(ast_root, data);
	execute_ast(ast_root, data);
	// printf("code: %d\n", data->status_code);
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
		if (!prompt)
			handle_malloc_error("readline", data);
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
