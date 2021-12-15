/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoshie <hyoshie@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:37:17 by hyoshie           #+#    #+#             */
/*   Updated: 2021/12/15 09:40:32 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <stdbool.h>

int	main(void)
{
	int	i;

	i = 0;
	while (true)
	{
		printf("[i]%d\n", i++);
		sleep(5);
	}
	return (0);
}
