/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erwfonta <erwfonta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:21 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/28 15:15:03 by erwfonta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*expand_var(char *str, int start, int *end, t_data *data)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	int		i;

	i = start + 1;
	if (!str[i] || (!is_valid_var_char(str[i]) && str[i] != '?'))
	{
		*end = start;
		return (str);
	}
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	*end = i;
	var_name = ft_substr(str, start + 1, i - (start + 1));
	if (!var_name)
		return (NULL);
	var_value = ft_getenv_content(data, var_name);
	if (!var_value)
		var_value = "";
	result = ft_strjoin3(
		ft_substr(str, 0, start),
		var_value,
		str + *end);
	free(var_name);
	free(str);
	return (result);
}

static char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	if (!str)
		return (NULL);
	result = gc_malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

void	expand_variables_in_node(t_ast_node *node, t_data *data)
{
	int		i;
	char	quote;
	int		var_end;

	if (!node || !node->args)
		return ;
	i = 0;
	while (node->args[i])
	{
		quote = 0;
		var_end = 0;
		while (node->args[i][var_end])
		{
			if (node->args[i][var_end] == '\'' && !quote)
				quote = '\'';
			else if (node->args[i][var_end] == '\"' && !quote)
				quote = '\"';
			else if (node->args[i][var_end] == quote)
				quote = 0;
			else if (node->args[i][var_end] == '$' && quote != '\'')
				node->args[i] = expand_var(node->args[i], var_end, &var_end,
						data);
			if (node->args[i])
				var_end++;
		}
		node->args[i] = remove_quotes(node->args[i]);
		i++;
	}
	expand_variables_in_node(node->left, data);
	expand_variables_in_node(node->right, data);
}

void	start_parsing(char *command_readed, t_data *data)
{
	t_token		*token;
	t_ast_node	*ast_root;

	(void)data;
	token = tokenization_input(command_readed);
	display_tokens(token);
	ast_root = parse_tokens(&token);
	// generate_ast_diagram(ast_root);
	check_here_doc(ast_root, data);
	execute_ast(ast_root, data);
	// printf("code: %d\n", data->status_code);
}

void	exec_readline(t_data *data)
{
	char	*command_readed;
	char	*prompt;
	char	*full_prompt;

	while (1)
	{
		set_signal_parent();
		if (g_signal_received != 0)
		{
			g_signal_received = 0;
			continue ;
		}
		prompt = getcwd(NULL, 0);
		if (!prompt)
			handle_malloc_error("readline", data);
		full_prompt = ft_strjoin3(BBLUE "→ ", prompt,
				BRED " minishell> " WHITE);
		gc_free(prompt);
		command_readed = readline(full_prompt);
		gc_free(full_prompt);
		if (command_readed == NULL)
			ft_exit(data, NULL);
		if (ft_strlen(command_readed) > 0)
			(add_history(command_readed), start_parsing(command_readed, data));
		gc_free(command_readed);
	}
}
