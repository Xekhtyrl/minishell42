/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:18:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/19 23:27:10 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ctrl_c(int num)
{
	num++;
	printf("\n"GREEN"MiniS̸"RED"Hell "NC);
}

void ctrl_d(void)
{
	printf("exit\n");
	exit(130);
}

void ctrl_bslash(int num)
{
	num++;
	printf(GREEN"Mini"NC"S̸"RED"Hell "NC);
}

void sign_handler(int code)
{
	if (code == SIGINT)
	{
		write(1,"\n",1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sign_handler);
}
