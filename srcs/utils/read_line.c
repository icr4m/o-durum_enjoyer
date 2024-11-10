/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:03:07 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/10 20:47:07 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_parsing(char *command_readed, t_data *data)
{
	t_token		*token;
	t_ast_node	*ast_root;

	(void)data;
	if (is_syntax_error(command_readed, data))
		return ;
	token = tokenization_input(command_readed);
	ast_root = parse_tokens(&token);
	expand_variables_in_node(ast_root, data);
	check_here_doc(ast_root, data);
	execute_ast(ast_root, data);
}

static char	*get_prompt(t_data *data)
{
	char	*prompt;
	char	*full_prompt;

	prompt = getcwd(NULL, 0);
	if (!prompt)
		handle_malloc_error("readline", data);
	full_prompt = ft_strjoin3(BBLUE "→ ", prompt, BRED " minishell> " WHITE);
	gc_free(prompt);
	return (full_prompt);
}

char	*ft_readline(t_data *data)
{
	char	*prompt;
	char	*command_readed;

	while (1)
	{
		prompt = get_prompt(data);
		command_readed = readline(prompt);
		gc_free(prompt);
		if (g_signal_received != 0)
		{
			set_info_signal(data);
			continue ;
		}
		if (!command_readed)
			ft_exit(data, NULL);
		else if (ft_strcmp(command_readed, "") == 0)
			gc_free(command_readed);
		else
			break ;
	}
	prompt = ft_strdup(command_readed);
	return (gc_free(command_readed), prompt);
}

void	exec_readline(t_data *data)
{
	char	*command_read;

	while (1)
	{
		set_signal_parent();
		command_read = ft_readline(data);
		start_parsing(command_read, data);
		add_history(command_read);
	}
}
