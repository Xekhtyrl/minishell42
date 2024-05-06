/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:41:02 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/06 14:50:02 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EE_H
# define EE_H

#include "../minishell.h"
# define ORDE "/bin/bash", (char*[]){"/bin/bash"
# define R_66 "./includes/ee/order66.sh", 0}, envp
# define WARNING "you went to deep in the mini(s)hell"
# define HIDDEN ", what could be hidden in those forsaken depth?!"

void execute_order_66(char **envp);

#endif