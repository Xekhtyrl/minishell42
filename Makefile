NAME = minishell

INCLUDES = ./includes

LIBFT = $(INCLUDES)/libft

MY_SOURCES =	main.c					\
				src/parsing.c			\
				src/parsing_utils.c		\
				src/parsing_utils2.c	\
				src/parsing_lst.c		\
				src/signal.c			\
				src/builtin/env.c		\
				src/builtin/export.c	\
				src/builtin/cd.c		\
				src/builtin/pwd.c		\
				src/builtin/echo.c		\
				src/builtin/unset.c		\
				src/builtin/exit.c		\
				src/utils/sort_list.c 	\
				src/execute.c 			\
				src/execute_utils.c 	\
				src/get_fd.c 			\
				src/get_path.c 			\
				src/dup.c				\
				src/free.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

C_GREEN = \033[0;32m

C_RED = \033[0;31m

C_BLUE = \033[0;34m

C_YEL = \033[0;34m

C_END=\033[0m

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

ifeq "$(USER)" "gfinet"
	# ifeq "$(HOMEBREW_CELLAR)" "/opt/homebrew/Cellar"
		# LFLAGS = -L /opt/homebrew/Cellar/readline/8.2.10/lib -I /opt/homebrew/Cellar/readline/8.2.10/include/readline/ -lreadline
	# else
		LFLAGS = -L /Users/gfinet/homebrew/Cellar/readline/8.2.10/lib -I /Users/gfinet/homebrew/Cellar/readline/8.2.10/include/readline -lreadline
	# endif
else
	LFLAGS = -L /Users/lvodak/.brew/opt/readline/lib -I /Users/lvodak/.brew/opt/readline/include -lreadline
endif

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@make -C $(LIBFT)
	@gcc $(CFLAGS) $(LFLAGS) -o $(NAME) $(MY_OBJECTS) $(LIBFT)/libft.a
	@echo "$(C_GREEN)$(NAME) compiled with $(CFLAGS)$(C_END)"
	@echo "$(C_RED)Welcome in our mini hell$(C_END)"
	@echo "$(C_GREEN)****      ***   *******   *****    ***   ******** $(C_END)$(C_YEL)                 $(C_RED)***     ***    *********   ****        ***         $(C_END)"
	@echo "$(C_GREEN)*--**    *+-*   ***-***   *---**   *-*   ***+-*** $(C_END)$(C_YEL)                 $(C_RED)*-*     *-*    *-*******   *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-++*   **--*     *-*     *-+****  *-*      *-*   $(C_END)$(C_YEL)        |        $(C_RED)*-*     *-*    *-*         *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-* ** **-*-*     *-*     *-*  *** *-*      *-*   $(C_END)$(C_YEL)     |  |  |     $(C_RED)*-*******-*    *-*******   *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-* ***** *-*     *-*     *-*   ****-*      *-*   $(C_END)$(C_YEL)     |  |  |     $(C_RED)*-*******-*    *-*******   *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-*  ***  *-*     *-*     *-*    **--*      *-*   $(C_END)$(C_YEL)  |  |  |  |  |  $(C_RED)*-*     *-*    *-*         *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-*       *-*   ***-***   *-*     **-*   ***+-*** $(C_END)$(C_YEL)  |  |  |  |  |  $(C_RED)*-*     *-*    *-*******   *--*******  *-********  $(C_END)"
	@echo "$(C_GREEN)***       ***   *******   ***      ***   ******** $(C_END)$(C_YEL)  |  |  |  |  |  $(C_RED)***     ***    *********   **********  **********  $(C_END)"
	@echo "                                                    $(C_YEL)|  |     |  |   	                   "
	@echo "                                                    $(C_YEL)|           |                 "
	@echo "$(C_GREEN)                                                         *****                                                        $(C_END)"  
	@echo "$(C_GREEN)                                                        ********                                                      $(C_END)"  
	@echo "$(C_GREEN)                                                  ***   *-*   ***                                                     $(C_END)"  
	@echo "$(C_GREEN)                                                  .**   ****   **                                                     $(C_END)"  
	@echo "$(C_GREEN)                                                   ***   *-*   ***                                                    $(C_END)"  
	@echo "$(C_GREEN)                                                    *** **-*                                                          $(C_END)"  
	@echo "$(C_GREEN)                                 .      *       .    *******         *   .$(C_END)"

%.o:	%.c
	@gcc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

add:
	git add Makefile src includes main.c .gitignore

clean:
	@rm -rf $(MY_OBJECTS) $(MY_OBJ_BONUS)
	@make -C $(LIBFT) clean
	@echo "$(C_RED)$(NAME) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)/libft.a
	@echo "$(C_RED)Update: Herobrine has been removed.$(C_END)"

re: fclean all

.PHONY: all clean fclean re