/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/24 12:36:55 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_readline(t_data *data)
{
	char	*command_readed;
	char	*prompt;
	char	*full_prompt;

	(void)data;
	while (1)
	{
		setup_sig_parent();
		if (g_signal_received != 0)
		{
			g_signal_received = 0;
			break ;
		}
		prompt = getcwd(NULL, 0);
		full_prompt = ft_strjoin3(BBLUE "→ ", prompt,
				BRED " minishell> " WHITE);
		free(prompt);
		command_readed = readline(full_prompt);
		free(full_prompt);
		if (command_readed == NULL)
			break ;
		if (ft_strlen(command_readed) > 0)
			add_history(command_readed);
		free(command_readed);
	}
}
