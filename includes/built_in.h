/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:56 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/25 19:01:56 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
/*
 * 1 pour print
 * 0 pour get
 */
char	*ft_pwd(t_data *data, int get_or_print);
void	ft_export(t_data *data, char *var_name, char *content);

#endif