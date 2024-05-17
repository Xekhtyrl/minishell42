/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:32:49 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/17 22:01:03 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"
#include <limits.h>

long long	ft_atoll(const char *str)
{
	int			f;
	long long	nbr;

	f = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (!ft_strncmp(str, "-9223372036854775808", ft_strlen(str)))
			return (LLONG_MIN);
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			f *= -1;
	}
	while (ft_isdigit(*str))
		nbr = nbr * 10 + (*str++ - '0');
	if (nbr > LLONG_MAX || (nbr == LLONG_MAX && f == -1) || nbr < 0)
		return (0);
	return (nbr * f);
}

int	ft_atoi(const char *str)
{
	int		f;
	long	nbr;

	f = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			f *= -1;
	}
	while (ft_isdigit(*str))
		nbr = nbr * 10 + (*str++ - '0');
	if (nbr > INT32_MAX || (nbr == INT32_MAX && f == -1) || nbr < 0)
		return (0);
	return (nbr * f);
}
