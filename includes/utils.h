/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:12:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/15 12:18:56 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

// READ LINE
void	exec_readline(t_data *data);

// EXIT

void	free_and_exit(int code);
void	handle_pipe_error(char *message, t_data *data);
void	handle_malloc_error(char *message, t_data *data);

// UTILS

char	**env_list_to_array(t_env *env_list);
void	init_minishell(t_data *data, char **envp);

// DEBUG
void	generate_ast_diagram(t_ast_node *root);

#endif