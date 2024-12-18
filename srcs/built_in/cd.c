/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:37:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/11/11 14:52:58 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_home(t_data *data)
{
	char	*home;

	home = ft_getenv_content(data, "HOME");
	if (!home)
	{
		ft_fprintf(2, "cd: HOME not set\n");
		data->status_code = 1;
		return ;
	}
	if (chdir(home) == -1)
	{
		ft_fprintf(2, "cd: %s: %s\n", home, strerror(errno));
		data->status_code = 1;
		return ;
	}
	data->status_code = 0;
}

int	go_to_old(t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_getenv_content(data, "OLDPWD");
	if (!oldpwd)
	{
		ft_fprintf(2, "cd: OLDPWD not set\n");
		data->status_code = 1;
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", oldpwd, strerror(errno));
		data->status_code = 1;
		return (1);
	}
	ft_fprintf(1, "%s\n", oldpwd);
	data->status_code = 0;
	return (0);
}

void	change_old_pwd_in_env(t_data *data, char *old_pwd)
{
	t_env	*env;

	env = search_in_env(data, "OLDPWD");
	if (env)
	{
		if (env->env_var)
		{
			gc_free(env->env_var);
			env->env_var = ft_strjoin("OLDPWD=", old_pwd);
			if (!env->env_var)
				handle_malloc_error("pwd", data);
		}
		else
		{
			env->env_var = ft_strjoin("OLDPWD=", old_pwd);
			if (!env->env_var)
				handle_malloc_error("pwd", data);
		}
	}
}

void	change_pwd_in_env(t_data *data, char *old_pwd)
{
	char	*new_pwd;
	t_env	*env;

	env = search_in_env(data, "PWD");
	if (env)
	{
		new_pwd = ft_pwd(data, 0);
		if (new_pwd)
		{
			if (env->env_var)
				gc_free(env->env_var);
			env->env_var = ft_strjoin("PWD=", new_pwd);
			if (!env->env_var)
				handle_malloc_error("PWD", data);
			gc_free(new_pwd);
			change_old_pwd_in_env(data, old_pwd);
		}
	}
	else
		change_old_pwd_in_env(data, old_pwd);
}

int	ft_cd(t_data *data, char **args)
{
	char	*old_pwd;

	old_pwd = ft_pwd(data, 0);
	if (!args[1] || (ft_strcmp(args[1], "~") == 0) || (ft_strcmp(args[1],
				"--") == 0))
		go_to_home(data);
	else if (args[2])
	{
		ft_fprintf(2, "bash: cd: too many arguments\n");
		return (gc_free(old_pwd), data->status_code = 1);
	}
	else if ((ft_strcmp(args[1], "-") == 0) && args[1])
	{
		if (go_to_old(data))
			return (gc_free(old_pwd), data->status_code = 1);
	}
	else if (chdir(args[1]) == -1)
	{
		ft_fprintf(2, "cd: no such file or directory: %s\n", args[1]);
		return (gc_free(old_pwd), data->status_code = 1);
	}
	change_pwd_in_env(data, old_pwd);
	change_old_pwd_in_env(data, old_pwd);
	gc_free(old_pwd);
	return (data->status_code = 0);
}
