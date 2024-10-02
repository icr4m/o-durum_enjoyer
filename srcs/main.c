/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 13:16:59 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	size_t	i;
	t_env	*current;
	char	*test2[4] = {"unset", "TEST", "ZDOTDIR", NULL};
	char	*test[4] = {"export", "TEST=test", "CACA=pipi", NULL};

	i = 0;
	(void)av;
	(void)ac;
	data.env = init_env(envp);
	ft_export(&data, test);
	ft_unset(&data, test2);
	current = data.env;
	while (current)
	{
		printf("%s\n", current->env_var);
		current = current->next;
	}
	exec_readline(&data);
	free_and_exit(EXIT_SUCCESS);
}
