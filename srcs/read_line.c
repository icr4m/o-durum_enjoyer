/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 11:40:21 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_readline(t_data *data)
{
	char	*command_readed;
	char	*prompt;

	(void)data;
	while (1)
	{
		setup_sig_parent();
		prompt = getcwd(NULL, 0);
		printf(BBLUE "→ %s " WHITE, prompt);
		command_readed = readline(BRED "minishell> " WHITE);
		free(prompt);
		if (command_readed == NULL && g_signal_received != 0)
		{
			g_signal_received = 0;
			continue ;
		}
		if (command_readed == NULL)
			break ;
		if (ft_strlen(command_readed) > 0)
			add_history(command_readed);
		free(command_readed);
	}
}
