/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:08:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/24 22:20:26 by gfinet           ###   ########.fr       */
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

//______________________EXECUTE________________________//
int	fill_fd(int *pipe[2], t_input *input);
int	execute_command(char **envp, t_input *cmd, int *pipe[2]);
int trad_input(t_input *cmd);
char	**get_path(char **envp);

//_______________________GET_FD________________________//
int *get_fd_infiles(t_input *input, int size);
int *get_fd_outfiles(t_input *input, int size);
int open_infile(t_arg_lst *tmp);
int open_outfile(t_arg_lst *tmp);

//________________________FREE_________________________//
void strarray_free(char **built);
int	send_error(int flag);

#endif