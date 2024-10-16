/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:53:48 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/16 18:14:24 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char **args)
{
	long	code;

	if (data->is_child != 1)
		printf("exit\n");
	if (!args)
		free_and_exit(data->status_code);
	if (!args[1])
		free_and_exit(data->status_code);
	if (args[2])
	{
		data->status_code = 1;
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		return ;
	}
	if (!ft_is_numeric(args[1]))
	{
		ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
			args[1]);
		free_and_exit(2);
	}
	ft_atol_safe(&code, args[1]);
	if (code < 0 || code > 255)
		code = code % 256;
	free_and_exit((int)code);
}
