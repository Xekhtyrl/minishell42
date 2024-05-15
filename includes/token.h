/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:05:00 by gfinet            #+#    #+#             */
/*   Updated: 2024/05/15 21:28:12 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define GREEN "\001\033[0;32m\x1b[1m\002"
# define LBLUE "\001\033[0;36m\x1b[1m\002"
# define BLUE "\001\033[0;34m\x1b[1m\002"
# define RED "\001\033[0;31m\x1b[1m\002"
# define WHITE "\001\033[0;30m\002"
# define NC "\001\033[0m\002"

# define BUILT_TK 12
# define WORD_TK 13
# define PIPE_TK 14
# define WRITE_TK 15
# define APPEN_TK 16
# define READ_TK 17
# define HEREDOC_TK 18
# define ENV_VAR_TK 19
# define SPACE_TK 20
# define CMD_TK 21
# define ENV_TK 22
# define ERROR_TK 23

# define FD_OUT 1
# define FD_IN 0

# define OPEN_ERR -1
# define READ_ERR -2
# define WRITE_ERR -3
# define FORK_ERR -4
# define MALLOC_ERR -5
# define PIPE_ERR -6
# define ARG_ERR -7
# define ACCESS_ERR -8
# define PERM_ERR -9
# define PATH_ERR -10
# define CMD_ERR -11
# define ARG_L_ERR -12

# define FILE_MSG 2
# define ARG_L_MSG 7
# define ALLOC_MSG 12
# define PERM_MSG 13
# define ARG_MSG 22
# define PIPE_MSG 32
# define CMD_MSG "command not found"

#endif