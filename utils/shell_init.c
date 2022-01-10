/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:26:31 by yshimazu          #+#    #+#             */
/*   Updated: 2022/01/10 17:57:56 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_dict	*init_pwd(t_dict *env)
{
	t_dict	*pwd;
	char	*key;
	char	*value;
	char	*pwd_value;

	pwd = xdict_new("", "");
	key = ft_xstrdup("pwd");
	pwd_value = dict_get_value("PWD", env);
	if (pwd_value)
		value = ft_xstrdup(pwd_value);
	else
		value = ft_xstrdup("");
	dict_addback(pwd, xdict_new(key, value));
	return (pwd);
}

t_info	*shell_init(void)
{
	t_info		*info;
	extern int	g_exit_status;

	info = xmalloc(sizeof(t_info));
	info->env = init_envs();
	info->pwd = init_pwd(info->env);
	save_stdfd(info);
	g_exit_status = 0;
	return (info);
}
