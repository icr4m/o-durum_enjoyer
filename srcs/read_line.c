/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 18:39:45 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec_readline(t_data *data)
// {
// 	char	*command_readed;
// 	char	*prompt;

// 	(void)data;
// 	while (1)
// 	{
// 		setup_sig_parent();
// 		prompt = getcwd(NULL, 0);
// 		printf(BBLUE "→ %s " WHITE, prompt);
// 		command_readed = readline(BRED "minishell> " WHITE);
// 		free(prompt);
// 		if (command_readed == NULL && g_signal_received != 0)
// 		{
// 			g_signal_received = 0;
// 			continue ;
// 		}
// 		if (command_readed == NULL)
// 			break ;
// 		if (ft_strlen(command_readed) > 0)
// 			add_history(command_readed);
// 		free(command_readed);
// 	}
// }

void	exec_readline(t_data *data)
{
	char	*input;
	t_token	*tokens;
	t_token	*current;

	(void)data;
	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		tokens = parse_input(input);
		current = tokens;
		while (current)
		{
			printf("Token: %s, Type: %d\n", current->value, current->type);
			current = current->next;
		}
		// free_tokens(tokens);
		free(input);
	}
}

char	*read_input(void)
{
	char	*command_readed;
	char	*prompt;

	setup_sig_parent();
	prompt = getcwd(NULL, 0);
	if (!prompt)
		return (NULL);
	printf(BBLUE "→ %s " WHITE, prompt);
	command_readed = readline(BRED "minishell> " WHITE);
	free(prompt);
	if (command_readed == NULL && g_signal_received != 0)
	{
		g_signal_received = 0;
		return (read_input());
	}
	if (command_readed == NULL)
		return (NULL);
	if (command_readed[0] != '\0')
		add_history(command_readed);
	return (command_readed);
}
