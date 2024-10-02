/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:37:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/03 00:44:08 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_home(t_data *data)
{
	char	*home;

	home = ft_getenv(data, "HOME");
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

void	go_to_old(t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_getenv(data, "OLDPWD");
	if (!oldpwd)
	{
		ft_fprintf(2, "cd: OLDPWD not set\n");
		data->status_code = 1;
		return ;
	}
	if (chdir(oldpwd) == -1)
	{
		ft_fprintf(2, "cd: %s: %s\n", oldpwd, strerror(errno));
		data->status_code = 1;
		return ;
	}
	ft_fprintf(1, "%s\n", oldpwd);
	data->status_code = 0;
}

void	change_old_pwd_in_env(t_data *data, char *old, char *old_pwd)
{
	t_env	*env;

	env = search_in_env(data, "OLDPWD");
	if (env)
	{
		if (env->env_var)
		{
			gc_free(env->env_var);
			env->env_var = old;
		}
		else
			env->env_var = old_pwd;
	}
}

void	change_pwd_in_env(t_data *data, char *old_pwd)
{
	char	*pwd;
	t_env	*env;

	env = search_in_env(data, "PWD");
	pwd = ft_getenv(data, "PWD");
	if (pwd)
	{
		env->env_var = ft_pwd(data, 0);
		change_old_pwd_in_env(data, pwd, old_pwd);
	}
	else
		change_old_pwd_in_env(data, NULL, old_pwd);
}

int	ft_cd(t_data *data, char **args)
{
	char	*old_pwd;

	old_pwd = ft_pwd(data, 0);
	if (args[2])
		ft_fprintf(2, "bash: cd: too many arguments");
	if (!args[1] || (ft_strncmp(args[1], "~", ft_strlen(args[1]) == 0))
		|| (ft_strncmp(args[1], "--", ft_strlen(args[1]) == 0)))
		go_to_home(data);
	else if (ft_strncmp(args[1], "-", ft_strlen(args[1]) == 0) && args[1])
		go_to_old(data);
	if (chdir(args[1]) == -1)
	{
		ft_fprintf(2, "cd: no such file or directory: %s", args[1]);
		return (data->status_code = 1);
	}
	change_pwd_in_env(data, old_pwd);
	free(old_pwd);
	return (data->status_code = 0);
}
