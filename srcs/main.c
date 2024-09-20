/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/20 03:46:01 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.envp = gc_malloc(sizeof(char **));
	data.envp = envp;
	exec_readline(&data);
	return (EXIT_SUCCESS);
}
