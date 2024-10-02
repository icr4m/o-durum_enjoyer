/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:56 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/03 00:42:45 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "minishell.h"

// CD
int		ft_cd(t_data *data, char **args);

// ENV
/*
 * 2 pour export
 * autre pour rien
 */
void	print_env(t_data *data, int cas);
int		ft_env(t_data *data, char **args);

// EXPORT
int		ft_export(t_data *data, char **args);

// ECHO
int		ft_echo(t_data *data, char **args);

// FT EXIT
void	ft_exit(t_data *data, char **args);

// INIT ENV
t_env	*search_in_env(t_data *data, const char *name);
t_env	*init_env(char **envp);
char	*ft_getenv(t_data *data, char *var_name);

// PWD
/*
 * 1 pour print
 * 0 pour get
 */
char	*ft_pwd(t_data *data, int get_or_print);

// UNSET
int		ft_unset(t_data *data, char **vars);

#endif