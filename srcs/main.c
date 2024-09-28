/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/28 16:29:18 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	size_t	i;
	t_env	*current;

	i = 0;
	(void)ac;
	(void)av;
	init_env(&data, envp);
	// ft_export(&data, "PROUT", "test");
	current = &data.env;
	while (current)
	{
		printf("%s\n", current->env_var);
		current = current->next;
	}
	exec_readline(&data);
	free_and_exit(&data);
}
