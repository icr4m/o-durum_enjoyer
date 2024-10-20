/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:40:40 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/20 21:51:31 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args)
{
	if (args[1] != NULL)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", args[1]);
		return (data->status_code = 127);
	}
	print_env(data, 1);
	return (data->status_code = 0);
}

void	print_env(t_data *data, int cas)
{
	t_env	*current;
	char	*equal_sign;

	current = data->env;
	while (current)
	{
		if (cas == 2)
		{
			equal_sign = ft_strchr(current->env_var, '=');
			if (equal_sign)
			{
				write(1, "export ", 7);
				write(1, current->env_var, equal_sign - current->env_var);
				printf("=\"%s\"\n", equal_sign + 1);
			}
			else
				printf("export %s\n", current->env_var);
		}
		else if (cas == 1)
		{
			if (ft_strchr(current->env_var, '='))
				printf("%s\n", current->env_var);
		}
		current = current->next;
	}
}
