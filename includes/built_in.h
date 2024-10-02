/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:56 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 11:09:52 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "minishell.h"

char	*search_in_env(t_data *data, char *content);
/*
 * 1 pour print
 * 0 pour get
 */
char	*ft_pwd(t_data *data, int get_or_print);
t_env	*init_env(char **envp);
int		ft_export(t_data *data, char **args);
int		ft_unset(t_data *data, char **vars);

#endif