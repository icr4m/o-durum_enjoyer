/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 01:38:53 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/20 01:55:06 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_data *data)
{
	char	*pwd_read;
	char	**splitted;
	size_t	index;

	index = 0;
	pwd_read = getcwd(pwd_read, 0);
	splitted = ft_split(pwd_read, '/');
	while (splitted[index] != NULL)
	{
        
	}
}
void	exec_readline(t_data *data)
{
	char	*prompt;
	char	*command_readed;

	while (1)
	{
		prompt = get_prompt(data);
	}
}
