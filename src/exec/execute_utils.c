/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:47:24 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/22 16:48:42 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_stradd(char *s1, char const *s2)
{
	size_t		j;
	size_t		i;
	char		*p;

	if (!s1 && !s2)
		return (0);
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (p == NULL)
		return (free(s1), NULL);
	while (s1 && i < ft_strlen(s1))
	{
		p[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2 && j < ft_strlen(s2))
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

char	**get_env(t_env *envp)
{
	char	**new;
	int		size;
	int		i;

	size = ft_lstsize((t_list *)envp);
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (0);
	i = -1;
	while (++i < size)
	{
		if (envp && envp->content)
		{
			new[i] = ft_strjoin(envp->var, "=");
			new[i] = ft_stradd(new[i], envp->content);
		}
		else if (envp)
			new[i] = ft_strdup(envp->var);
		envp = envp->next;
	}
	new[i] = 0;
	return (new);
}

int	in_str_array(char *str, char **lst)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(str);
	while (lst[i] && ft_strncmp(str, lst[i], size))
	{
		size = ft_strlen(str);
		i++;
	}
	if (!lst[i])
		return (0);
	return (1);
}

int	in_int_array(int t, int *l, int size)
{
	int	i;

	i = -1;
	while (l && i + 1 < size && l[++i])
		if (t == l[i])
			return (1);
	return (0);
}

void	print_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("%s\n", str[i++]);
}
