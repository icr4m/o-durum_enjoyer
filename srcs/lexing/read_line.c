/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/20 04:43:05 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt(t_data *data)
{
	char	*pwd_read;
	size_t	index;

	index = 0;
	pwd_read = getcwd(NULL, 0);
	while (*pwd_read != '\0')
	{
		if (ft_strncmp(pwd_read, get_user(data), 4) == 0)
			return (pwd_read + ft_strlen(get_user(data)) + 1);
		pwd_read++;
	}
	return (NULL);
}

void	exec_readline(t_data *data)
{
	char	*prompt;
	char	*command_readed;

	while (1)
	{
		prompt = ft_strjoin(get_user(data), "@madeprout:");
		prompt = ft_strjoin(prompt, get_prompt(data));
		prompt = ft_strjoin(prompt, ":~$");
		command_readed = readline((prompt));
	}
}
