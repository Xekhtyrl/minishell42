/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:18:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/19 19:32:54 by gfinet           ###   ########.fr       */
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
		printf("\n");
		rl_on_new_line();
	}
}

void set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sign_handler);
}