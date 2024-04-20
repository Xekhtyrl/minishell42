/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:18:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/19 23:26:00 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ctrl_c(int num)
{
	if (SIGINT == num)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void ctrl_d(void)
{
	printf("exit\n");
	exit(0);
}

void ctrl_bslash(int num)
{
	num++;
	printf(GREEN"Mini"NC"S̸"RED"Hell "NC);
}

void set_signals(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_bslash);
}