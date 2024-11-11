/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:14:26 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 12:24:30 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lexing.h"

// EXEC COMMAND

void	check_directory(t_ast_node *node);
void	exec_command(t_ast_node *node, t_data *data);
void	exec_command_other(t_ast_node *node, t_data *data);

// EXEC UTILS

int		ft_open_infile(char *file, int flags, t_data *data);
int		ft_open_outfile(char *file, int flags, t_data *data);
void	ft_close(int fd);
char	*find_path(char *command, t_data *data);
int		ft_access_stat(char *path);

// APPEND
int		handle_heredoc_out(t_ast_node *node, t_data *data);

// EXEC
void	close_heredocs(t_ast_node *root);
void	execute_ast(t_ast_node *node, t_data *data);

// EXIT STATUS

void	exit_status(int status, t_data *data);

// FORK

int		ft_fork(t_data *data);

// HEREDOC
char	*get_temp_filename(t_data *data);
int		create_heredoc(char *delimiter, t_data *data);
void	check_here_doc(t_ast_node *node, t_data *data);
void	execute_heredoc_redirection(t_ast_node *node, t_data *data);

// PIPEX EXEC

/*
** @brief Execute les commandes autour d'un pipe
** @param node Noeud de l'AST contenant les commandes à pipe
** @param data Structure contenant les données globales du shell
** @return None, exit en cas d'erreur
*/
void	pipe_exec(t_ast_node *node, t_data *data);

// REDIRECTION

int		handle_multiple_redirections(t_ast_node *node, t_data *data);
int		handle_redirection_in(t_ast_node *node, t_data *data);
int		handle_redirection_out(t_ast_node *node, t_data *data);

#endif