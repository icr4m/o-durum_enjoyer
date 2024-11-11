/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:26:46 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 16:50:47 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_classic_prompt(t_data *data)
{
	char	*pwd;
	char	*full_prompt;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		handle_malloc_error("readline", data);
	pwd = ft_strjoin3("[", pwd, "]");
	full_prompt = ft_strjoin3(BPurple "→ " BBLUE, pwd,
			BRED " minishell> " WHITE);
	gc_free(pwd);
	return (full_prompt);
}

char	*get_prompt(t_data *data)
{
	char	*home;
	char	*pwd;
	char	*full_prompt;

	full_prompt = NULL;
	pwd = ft_pwd(data, 0);
	if (!pwd)
		handle_malloc_error("readline", data);
	home = ft_getenv_content(data, "HOME");
	if (!home)
		return (gc_free(pwd), get_classic_prompt(data));
	if (ft_strcmp(pwd, home) && pwd[ft_strlen(home)] == '/')
		full_prompt = ft_strjoin3(BPurple "→ 🏠︎" BBLUE, pwd + ft_strlen(home),
				BRED " minishell> " WHITE);
	else
		return (gc_free(pwd), get_classic_prompt(data));
	gc_free(pwd);
	return (full_prompt);
}
