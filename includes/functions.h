/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:08:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/24 17:10:55 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "libft/headers/ft_printf.h"
# include "structures.h"

void		print_input_lst(t_input	*input);
//______________________PARSING_______________________//
t_input		*parse(char *str);
//___________________PARSING_UTILS____________________//
int			is_white_space(char c);
int			is_not_sep(char c);
int			closed_quotes(char *str);
int			check_for_pipe(char *str);
int			get_token_type(char *c, int start);
//____________________PARSING_LST_____________________//
t_arg_lst	*arg_node(int type, char *token);
t_input		*create_node(char *str, int type);
void 		set_input(t_input *cmd, char *token, int type);

char	*pick_title();

//_______________________SIGNAL________________________//
void ctrl_c(int num);
void ctrl_d(void);
void set_signals(void);

#endif