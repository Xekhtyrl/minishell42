/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:32:52 by lvodak            #+#    #+#             */
/*   Updated: 2024/04/07 21:04:33 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned long	i;

	if (count * size > UINT32_MAX)
		return (0);
	i = 0;
	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
