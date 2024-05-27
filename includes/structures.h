/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:06:11 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/27 17:32:09 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_env
{
	struct s_env	*next;
	char			*var;
	int				flag;
	struct s_env	*prev;
	char			*content;
}	t_env;

typedef struct s_arg_lst
{
	struct s_arg_lst	*next;
	char				*token;
	int					type;
	struct s_arg_lst	*prev;
}	t_arg_lst;

typedef struct s_input
{
	struct s_input		*next;
	char				*token;
	int					type;
	t_arg_lst			*arg;
}	t_input;

typedef struct s_cmd_info
{
	int		size;
	int		pipe[2];
	t_env	**env;
	char	**envtb;
	pid_t	*proc;
}	t_cmd_info;

#endif