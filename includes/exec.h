/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:14:26 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/04 16:09:57 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lexing.h"

// EXEC UTILS

int		ft_open_infile(char *file, int flags, t_data *data);
int		ft_open_outfile(char *file, int flags, t_data *data);

// EXEC

void	execute_ast(t_ast_node *node, t_data *data);

// PIPEX EXEC

void	pipe_exec(t_ast_node *node, t_data *data);

#endif