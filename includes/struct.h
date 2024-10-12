/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:51:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/12 16:04:49 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "minishell.h"

typedef struct s_env
{
	char				*env_var;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	int					status_code;
	bool				is_child;
	struct s_env		*env;
	struct s_ast_node	*ast_node;
}						t_data;

#endif