/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:19:07 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/12 18:49:09 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*ft_strjoin_f(char *s1, char const *s2, int fr)
{
	char	*s3;
	int		j;

	if (!s2)
		return (s1);
	if (!s1)
		return ((char *)s2);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	j = -1;
	while (s1[++j] != '\0')
		s3[j] = s1[j];
	if (fr)
		free(s1);
	while (*s2 != '\0')
		s3[j++] = *s2++;
	s3[j] = '\0';
	return (s3);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		j;

	if (!s2 || !s1)
		return (0);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	j = 0;
	while (*s1 != '\0')
		s3[j++] = *s1++;
	while (*s2 != '\0')
		s3[j++] = *s2++;
	s3[j] = '\0';
	return (s3);
}
