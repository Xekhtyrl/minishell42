/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:18:05 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/14 22:36:19 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d(t_env **envp)
{
	rl_clear_history();
	printf("exit\n");
	//system(("leaks minishell"));
	free_env(envp);
	exit(130);
}

void	sign_handler(int code)
{
	if (code == SIGINT)
	{
		write(1, "\n", 1);
		if (g_ret_val != -1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		// printf("g = %i\n", g_ret_val);
		// g_ret_val = 1;
	}
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, &sign_handler);
}
