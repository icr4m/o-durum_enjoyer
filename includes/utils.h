/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:12:32 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/12 19:11:35 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

// INIT MINISHELL

void		init_minishell(t_data *data, char **envp);

// EXPAND VAR
void		expand_variables_in_node(t_ast_node *node, t_data *data);

char		*remove_quotes(char *str);
int			find_var_end(char *str, int start);
char		*get_var_name(char *str, int start, int end);
char		*handle_empty_or_null(char *str, int start, int *end);
char		*handle_question_mark(char *str, int start, int *end, t_data *data);
char		*process_string(char *str, t_data *data);

// PROMPT
char		*get_classic_prompt(t_data *data);
char		*get_prompt(t_data *data);

// READ LINE
void		exec_readline(t_data *data);

// EXIT

void		free_and_exit(int code);
void		handle_pipe_error(char *message, t_data *data);
void		handle_malloc_error(char *message, t_data *data);

// UTILS

char		**env_list_to_array(t_env *env_list, t_data *data);

// DEBUG
void		generate_ast_diagram(t_ast_node *root);

#endif