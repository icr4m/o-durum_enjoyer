/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:52 by rsk               #+#    #+#             */
/*   Updated: 2024/10/03 19:27:14 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*cmd_node;
	int			arg_count;

	cmd_node = create_ast_node(TOKEN_WORD);
	arg_count = count_cmd_args(*token);
	cmd_node->args = gcmalloc(sizeof(char *) * (arg_count + 1));
	if (!cmd_node->args)
		return (NULL);
	fill_cmd_args(cmd_node, *token, arg_count);
	return (cmd_node);
}

t_ast_node	*create_file_node(void);

