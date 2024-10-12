/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:48:26 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/25 19:07:00 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(t_data *data, int get_or_print)
{
	char	*temp;

	(void)data;
	temp = getcwd(NULL, 0);
	if (get_or_print == 1)
		printf("%s\n", temp);
	else if (get_or_print == 0)
		return (temp);
	free(temp);
	return (NULL);
}
