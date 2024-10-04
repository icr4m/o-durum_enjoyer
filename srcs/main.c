/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/04 16:04:11 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_node(t_ast_node *node, char **av)
{
	node->type = TOKEN_PIPE;
	node->left = gc_malloc(sizeof(t_ast_node));
	node->right = gc_malloc(sizeof(t_ast_node));
	node->left->type = TOKEN_WORD;
	node->left->args = gc_malloc(2 * sizeof(char *));
	node->left->args[0] = av[1];
	node->left->args[1] = NULL;
	node->left->left = NULL;
	node->left->right = NULL;
	node->right->type = TOKEN_WORD;
	node->right->args = gc_malloc(2 * sizeof(char *));
	node->right->args[0] = av[2];
	node->right->args[1] = NULL;
	node->right->left = NULL;
	node->right->right = NULL;
	node->args = NULL;
}
int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_ast_node	node;

	(void)ac;
	data.env = init_env(envp);
	fill_node(&node, av);
	exec
	// exec_readline(&data);
	free_and_exit(0);
}
