/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/08 10:12:00 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_side(t_ast_node *node, char **av, int start, int end)
{
	int	i;
	int	arg_count;

	node->type = TOKEN_WORD;
	arg_count = (end == -1) ? 0 : end - start + 1;
	if (end == -1)
	{
		while (av[start + arg_count])
			arg_count++;
	}
	node->args = gc_malloc((arg_count + 1) * sizeof(char *));
	i = 0;
	while (i < arg_count)
	{
		node->args[i] = av[start + i];
		i++;
	}
	node->args[i] = NULL;
	node->left = NULL;
	node->right = NULL;
}

void	fill_node(t_ast_node *node, char **av)
{
	int	i;
	int	pipe_index;
	int	arg_count;

	i = 1;
	pipe_index = -1;
	arg_count = 0;
	while (av[i])
	{
		if (av[i][0] == '|' && av[i][1] == '\0')
		{
			pipe_index = i;
			break ;
		}
		i++;
		arg_count++;
	}
	node->type = (pipe_index != -1) ? TOKEN_PIPE : TOKEN_WORD;
	if (pipe_index != -1)
	{
		node->left = gc_malloc(sizeof(t_ast_node));
		node->right = gc_malloc(sizeof(t_ast_node));
		fill_side(node->left, av, 1, pipe_index - 1);
		fill_side(node->right, av, pipe_index + 1, -1);
	}
	else
	{
		node->left = NULL;
		node->right = NULL;
		node->args = gc_malloc((arg_count + 1) * sizeof(char *));
		i = 0;
		while (i < arg_count)
		{
			node->args[i] = av[i + 1];
			i++;
		}
		node->args[i] = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	// t_ast_node	node;

	(void)ac;
	(void)av;
	data.env = init_env(envp);
	// fill_node(&node, av);
	// execute_ast(&node, &data);
	exec_readline(&data);
	free_and_exit(data.status_code);
}
