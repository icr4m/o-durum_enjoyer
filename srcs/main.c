/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/09 19:05:28 by ijaber           ###   ########.fr       */
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
		while (av[start + arg_count] && av[start + arg_count][0] != '<'
			&& av[start + arg_count][0] != '>' && ft_strncmp(av[start
				+ arg_count], "<<", 2) != 0 && ft_strncmp(av[start + arg_count],
				">>", 2) != 0)
			arg_count++;
	}
	node->args = gc_malloc((arg_count + 1) * sizeof(char *));
	i = 0;
	while (i < arg_count && av[start + i][0] != '<' && av[start + i][0] != '>'
		&& ft_strncmp(av[start + i], "<<", 2) != 0 && ft_strncmp(av[start + i],
			">>", 2) != 0)
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
	int	special_index;
	int	arg_count;

	i = 1;
	special_index = -1;
	arg_count = 0;
	while (av[i])
	{
		if ((av[i][0] == '|' || av[i][0] == '<' || av[i][0] == '>')
			&& av[i][1] == '\0')
		{
			special_index = i;
			break ;
		}
		else if ((ft_strncmp(av[i], "<<", 2) == 0 || ft_strncmp(av[i], ">>",
					2) == 0) && av[i][2] == '\0')
		{
			special_index = i;
			break ;
		}
		i++;
		arg_count++;
	}
	if (special_index != -1)
	{
		if (av[special_index][0] == '|')
			node->type = TOKEN_PIPE;
		else if (ft_strncmp(av[special_index], "<<", 2) == 0)
			node->type = TOKEN_REDIR_HEREDOC;
		else if (ft_strncmp(av[special_index], ">>", 2) == 0)
			node->type = TOKEN_REDIR_APPEND;
		else if (av[special_index][0] == '>')
			node->type = TOKEN_REDIR_OUT;
		else
			node->type = TOKEN_REDIR_IN;
		node->left = gc_malloc(sizeof(t_ast_node));
		node->right = gc_malloc(sizeof(t_ast_node));
		fill_side(node->left, av, 1, special_index - 1);
		if (node->type != TOKEN_PIPE)
		{
			node->right->type = TOKEN_WORD;
			node->right->args = gc_malloc(2 * sizeof(char *));
			node->right->args[0] = av[special_index + 1];
			node->right->args[1] = NULL;
			node->right->left = NULL;
			node->right->right = NULL;
		}
		else
		{
			fill_side(node->right, av, special_index + 1, -1);
		}
	}
	else
	{
		node->type = TOKEN_WORD;
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
	t_ast_node	node;

	(void)ac;
	// (void)av;
	data.env = init_env(envp);
	fill_node(&node, av);
	execute_ast(&node, &data);
	exec_readline(&data);
	free_and_exit(data.status_code);
}
