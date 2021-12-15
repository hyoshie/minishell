/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:26:31 by yshimazu          #+#    #+#             */
/*   Updated: 2021/12/15 17:40:54 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_info	*shell_init(void)
{
	t_info		*info;

	info = xmalloc(sizeof(t_info));
	info->env = init_envs();
	save_stdfd(info);
	info->exit_status = 0;
	return (info);
}