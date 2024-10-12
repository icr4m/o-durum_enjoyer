/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:40:40 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/04 16:44:04 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args)
{
	if (args[1] != NULL)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", args[1]);
		return (EXIT_FAILURE);
	}
	print_env(data, 1);
	return (EXIT_SUCCESS);
}

void	print_env(t_data *data, int cas)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (cas == 2)
			printf("export ");
		printf("%s\n", current->env_var);
		current = current->next;
	}
}
