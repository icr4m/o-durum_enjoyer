/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:15:04 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/04 16:58:10 by ijaber           ###   ########.fr       */
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
	t_data	data;

	(void)ac;
	data.env = init_env(envp);
	if (!ft_strcmp("cd", av[1]))
	{
		printf("PWD ENV: %s\n", ft_getenv_total(&data, "PWD"));
		printf("OLDPWD ENV: %s\n", ft_getenv_total(&data, "OLDPWD"));
		ft_cd(&data, av + 1);
		printf("PWD ENV: %s\n", ft_getenv_total(&data, "PWD"));
		printf("OLDPWD ENV: %s\n", ft_getenv_total(&data, "OLDPWD"));
	}
	else if (!ft_strcmp("echo", av[1]))
		ft_echo(&data, av + 1);
	else if (!ft_strcmp("env", av[1]))
		ft_env(&data, av + 1);
	else if (!ft_strcmp("exit", av[1]))
		ft_exit(&data, av + 1);
	else if (!ft_strcmp("export", av[1]))
		ft_export(&data, av + 1);
	else if (!ft_strcmp("unset", av[1]))
		ft_unset(&data, av + 1);
	// exec_readline(&data);
	free_and_exit(data.status_code);
}
