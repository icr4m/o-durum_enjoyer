/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/23 04:22:38 by ijaber           ###   ########.fr       */
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
		prompt = getcwd(NULL, 0);
		printf(BBlue "→ %s " White, prompt);
		command_readed = readline(BRed "minishell> " White);
		free(prompt);
		if (command_readed == NULL)
			break ;
		if (ft_strlen(command_readed) > 0)
			add_history(command_readed);
		free(command_readed);
	}
}
