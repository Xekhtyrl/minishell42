/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:05:00 by gfinet            #+#    #+#             */
/*   Updated: 2024/04/28 15:23:23 by gfinet           ###   ########.fr       */
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

// "\[\e[1;34m\]\u@\h:\w \$\[\e[0m\] "

# define BUILT_TK 12
# define WORD_TK 13
# define PIPE_TK 14
# define WRITE_TK 15
# define APPEN_TK 16
# define READ_TK 17
# define HEREDOC_TK 18
# define ENV_VAR_TK 19
# define SPACE_TK 20

#endif