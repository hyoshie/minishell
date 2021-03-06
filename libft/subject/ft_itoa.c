/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoshie <hyoshie@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:15:29 by hyoshie           #+#    #+#             */
/*   Updated: 2021/09/06 17:15:29 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	get_len_int(long l_nbr)
{
	long	cnt;

	cnt = 0;
	if (l_nbr < 0)
	{
		l_nbr = l_nbr * (-1);
		cnt++;
	}
	while (l_nbr >= 10)
	{
		l_nbr = l_nbr / 10;
		cnt++;
	}
	cnt++;
	return (cnt);
}

static char	*set_nbr(char *str, long l_nbr, long digit)
{
	str[digit] = '\0';
	if (l_nbr == 0)
		str[0] = '0';
	else
	{
		if (l_nbr < 0)
		{
			l_nbr = l_nbr * (-1);
			str[0] = '-';
		}
		while (l_nbr)
		{
			digit--;
			str[digit] = '0' + l_nbr % 10;
			l_nbr = l_nbr / 10;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	l_nbr;
	long	digit;

	l_nbr = (long)n;
	digit = get_len_int(l_nbr);
	str = (char *)malloc(sizeof(char) * (digit + 1));
	if (str == NULL)
		return (NULL);
	str = set_nbr(str, l_nbr, digit);
	return (str);
}
