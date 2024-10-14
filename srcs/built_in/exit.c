/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:53:48 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/14 19:12:11 by ijaber           ###   ########.fr       */
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
	if (arg_count > 2)
	{
		data->status_code = 130;
		ft_fprintf(2, "minishell: exit: too many arguments");
	}
	if (arg_count == 1)
		free_and_exit(data->status_code);
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
