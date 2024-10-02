/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/03 00:44:50 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*test[100] = {"cd", "~", NULL};

	(void)ac;
	(void)av;
	data.env = init_env(envp);
	ft_pwd(&data, 1);
	ft_cd(&data, test);
	ft_pwd(&data, 1);
	// exec_readline(&data);
	free_and_exit(0);
}
