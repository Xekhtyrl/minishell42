/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:41:02 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/07 15:16:31 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EE_H
# define EE_H

# include "../minishell.h"
# define ORDER66 "./includes/ee/order66.sh"
# define WARNING "you went to deep in the mini(s)hell"
# define HIDDEN ", what could be hidden in those forsaken depth?!"

void	execute_order_66(char **envp);
void	print_exporto_patronum(void);

#endif