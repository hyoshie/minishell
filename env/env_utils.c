/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:14:08 by yshimazu          #+#    #+#             */
/*   Updated: 2022/01/10 17:22:34 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	shlvl_update(t_dict *env)
{
	int	shlvl;

	shlvl = ft_atoi(dict_get_value("SHLVL", env));
	shlvl++;
	if (shlvl > 1000)
	{
		ft_putstr_fd("bash: warning: shell level (1000) too high, \
		resetting to 1", STDERR_FILENO);
		shlvl = 1;
	}
	dict_update_value(ft_xstrdup("SHLVL"), ft_itoa(shlvl), env);
}

t_dict	*init_envs(void)
{
	t_dict		*env;
	extern char	**environ;
	size_t		i;

	env = xdict_new("", "");
	i = 0;
	if (!environ || !environ[0])
		return (env);
	while (environ[i])
		dict_addback(env, dict_xstore_item(environ[i++], "="));
	shlvl_update(env);
	dict_delone(dict_search_item("_", env));
	dict_delone(dict_search_item("OLDPWD", env));
	dict_addback(env, xdict_new(ft_xstrdup("OLDPWD"), NULL));
	return (env);
}
