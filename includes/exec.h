/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:14:26 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 11:01:23 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lexing.h"

// EXEC COMMAND

void	exec_command(t_ast_node *node, t_data *data);
void	exec_command_other(t_ast_node *node, t_data *data);

// EXEC UTILS

int		ft_open_infile(char *file, int flags, t_data *data);
int		ft_open_outfile(char *file, int flags, t_data *data);
void	ft_close(int fd);
char	*find_path(char *command, t_data *data);
int		ft_access_stat(char *path);

// EXEC

void	execute_ast(t_ast_node *node, t_data *data);

// EXIT STATUS

void	exit_status(int status, t_data *data);

// FORK

int		ft_fork(t_data *data);

// PIPEX EXEC

void	pipe_exec(t_ast_node *node, t_data *data);

#endif