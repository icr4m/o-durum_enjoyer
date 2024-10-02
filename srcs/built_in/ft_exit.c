/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:53:48 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 16:08:18 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char **args)
{
	size_t	arg_count;
	long	code;

	arg_count = 1;
	while (args[arg_count])
		arg_count++;
	printf("exit\n");
	if (arg_count > 2)
	{
		data->status_code = 130;
		printf("minishell: exit: too many arguments");
	}
	if (arg_count == 1)
		exit(data->status_code);
	if (arg_count == 2)
	{
		if (ft_atol_safe(&code, args[1]) == 0)
			data->status_code = 2;
		free_and_exit(data->status_code);
	}
}

std