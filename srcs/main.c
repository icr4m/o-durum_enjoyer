/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 14:24:55 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*test2[4] = {"export", NULL};
	char	*test[4] = {"export", "TEST=test", "caca=", NULL};

	(void)av;
	(void)ac;
	data.env = init_env(envp);
	ft_export(&data, test);
	ft_export(&data, test2);
	exec_readline(&data);
	free_and_exit(EXIT_SUCCESS);
}
