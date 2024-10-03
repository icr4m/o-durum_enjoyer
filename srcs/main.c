/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/03 15:50:01 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	// char	*test[100] = {"cd", NULL};
	(void)ac;
	// (void)av;
	data.env = init_env(envp);
	printf("PWD ENV: %s\n", ft_getenv_total(&data, "PWD"));
	printf("OLDPWD ENV: %s\n", ft_getenv_total(&data, "OLDPWD"));
	ft_cd(&data, av + 1);
	printf("PWD ENV: %s\n", ft_getenv_total(&data, "PWD"));
	printf("OLDPWD ENV: %s\n", ft_getenv_total(&data, "OLDPWD"));
	// exec_readline(&data);
	free_and_exit(0);
}
