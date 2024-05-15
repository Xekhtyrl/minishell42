/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:58:13 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/15 20:18:43 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_number(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = (s[0] == '-');
	if (i && len == 1)
		return (0);
	while (i < len)
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	equal_int(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!is_number(s1))
		return (0);
	if (s1[0] == '-' && s1[0] == s2[0])
		i++;
	j = i;
	while (s1[i] == '0')
		i++;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	if (s1[i] != s2[j])
		return (0);
	return (1);
}

void	good_exit(int nbr, t_arg_lst *tmp)
{
	char		*nb_c;
	
	if (nbr == 1) 									// 1 arg
	{
		nbr = ft_atoi(tmp->token);
		nb_c = ft_itoa(nbr);
		if (equal_int(tmp->token, nb_c)) 				// arg est int
		{
			free(nb_c);
			printf("exit\n");
			exit(nbr % 256);
		}
		else 											//arg pas int
		{
			free(nb_c);
			printf("exit\n");
			send_error(ARG_ERR); // numeric argument required
			exit(255);
		}
	}
	else
		send_error(ARG_ERR);
}

int	ft_exit(t_arg_lst *arg)
{
	int			nbr;
	t_arg_lst	*tmp;

	tmp = arg;
	nbr = ft_lstsize((t_list *)tmp);
	if (!tmp)
	{
		printf("exit\n");
		exit(0);
	}
	else if (tmp && !is_number(tmp->token))
	{
		printf("exit\n");
		send_error(ARG_ERR);
		exit(255);
	}
	else if (tmp) 									// 1er arg est num
		good_exit(nbr, tmp);
	return (1);
}


/*
exit [lettre] [...] = exit + numeric arg need
exit [nombre] 	    = exit + nombre en ret
exit [nombre] [...] = no exit + too much arg
*/