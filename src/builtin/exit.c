/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:58:13 by lvodak            #+#    #+#             */
/*   Updated: 2024/05/28 22:20:51 by lvodak           ###   ########.fr       */
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

void	good_exit(long long nbr, t_arg_lst *tmp, int pr, t_input *cmd)
{
	char		*nb_c;

	if (nbr == 1)
	{
		nbr = ft_atoll(tmp->token);
		nb_c = ft_lltoa(nbr);
		if (equal_int(tmp->token, nb_c))
		{
			free(nb_c);
			if (pr)
				printf("exit\n");
			return (free_exit(&cmd, pr), exit(nbr));
		}
		else
		{
			free(nb_c);
			if (pr)
				printf("exit\nexit : %s : numeric argument required, ",
					tmp->token);
			send_error(ARG_ERR);
			return (free_exit(&cmd, pr), exit(255));
		}
	}
	else
		send_error(ARG_ERR);
}

int	ft_exit(t_arg_lst *arg, int pr, t_cmd_info *inf, t_input *cmd)
{
	int			nbr;
	t_arg_lst	*tmp;

	if (arg && arg->type == SPACE_TK && arg->next)
		arg = arg->next;
	tmp = arg;
	nbr = ft_lstsize((t_list *)tmp);
	if (pr)
		free_info(inf);
	if (!tmp)
	{
		if (pr)
			printf("exit\n");
		return (free_exit(&cmd, pr), exit(0), 0);
	}
	else if (tmp && !is_number(tmp->token))
	{
		if (pr)
			printf("exit\nexit : %s : numeric argument required, ", arg->token);
		return (send_error(ARG_ERR), free_exit(&cmd, pr), exit(255), 0);
	}
	else if (tmp)
		good_exit(nbr, tmp, pr, cmd);
	return (1);
}

void	check_exit_error(t_arg_lst *arg)
{
	int	nbr;

	nbr = ft_lstsize((t_list *)arg);
	if (arg && (!is_number(arg->token) || ft_strlen(arg->token) > 10))
	{
		if (!is_number(arg->token))
			printf("exit\nexit : %s : numeric argument required, ", arg->token);
		if (ft_strlen(arg->token) > 10)
			printf("exit\nexit : %s : numeric argument required, ", arg->token);
		send_error(ARG_ERR);
	}
	else if (arg && nbr > 2)
		send_error(ARG_L_ERR);
}
