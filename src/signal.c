/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:18:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/17 23:16:20 by gfinet           ###   ########.fr       */
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