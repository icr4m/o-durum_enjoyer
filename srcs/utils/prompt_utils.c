/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:26:46 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 18:03:59 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_classic_prompt(t_data *data)
{
	char	*pwd;
	char	*prompt;
	char	*full_prompt;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		handle_malloc_error("readline", data);
	prompt = ft_strjoin3("[", pwd, "]");
	gc_free(pwd);
	full_prompt = ft_strjoin3(BPurple "→ " BBLUE, prompt,
			BRED " minishell> " WHITE);
	gc_free(prompt);
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
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0
		&& pwd[ft_strlen(home)] == '/')
		full_prompt = ft_strjoin3(BPurple "→ 🏠︎" BBLUE, pwd + ft_strlen(home),
				BRED " minishell> " WHITE);
	else
		return (gc_free(pwd), get_classic_prompt(data));
	gc_free(pwd);
	return (full_prompt);
}
