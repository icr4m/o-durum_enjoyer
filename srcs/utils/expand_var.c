/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:59:05 by rsk               #+#    #+#             */
/*   Updated: 2024/11/07 18:48:28 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

static void	expand_args(char **args, t_data *data)
{
	int		i;
	char	*expanded;
	char	*unquoted;

	i = 0;
	while (args[i])
	{
		expanded = process_string(args[i], data);
		if (expanded)
		{
			unquoted = remove_quotes(expanded);
			if (unquoted)
				args[i] = unquoted;
		}
		i++;
	}
}

void	expand_variables_in_node(t_ast_node *node, t_data *data)
{
	if (!node)
		return ;
	if (is_redirection(node->type))
	{
		expand_variables_in_node(node->left, data);
		expand_variables_in_node(node->right, data);
		return ;
	}
	if (node->args)
		expand_args(node->args, data);
	expand_variables_in_node(node->left, data);
	expand_variables_in_node(node->right, data);
}
