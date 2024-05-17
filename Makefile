NAME = minishell

MY_SOURCES =	main.c							\
				includes/ee/ee.c				\
				src/parsing/parsing.c			\
				src/parsing/parsing_utils.c		\
				src/parsing/parsing_utils2.c	\
				src/parsing/parsing_lst.c		\
				src/parsing/clear_parse.c		\
				src/builtin/env.c				\
				src/builtin/export.c			\
				src/builtin/cd.c				\
				src/builtin/pwd.c				\
				src/builtin/echo.c				\
				src/builtin/unset.c				\
				src/builtin/exit.c				\
				src/utils/sort_list.c 			\
				src/utils/lst_to_tab.c			\
				src/env/env_var_utils.c			\
				src/env/setup_env.c				\
				src/env/setup_env_bis.c			\
				src/signal.c					\
				src/execute.c 					\
				src/execute_utils.c 			\
				src/get_fd.c 					\
				src/get_path.c 					\
				src/traduction.c 				\
				src/dup.c						\
				src/heredoc.c					\
				src/free.c						\
				src/free_input.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

C_GREEN = \033[0;32m

C_RED = \033[0;31m

C_BLUE = \033[0;34m

C_BPURP = \033[1;35m

C_END=\033[0m

CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address

ifeq "$(USER)" "lvodak"
	READLINE_PATH = $(HOME)/.brew/Cellar/readline/8.2.10/
else
	#READLINE_PATH = /opt/homebrew/Cellar/readline/8.2.10/
	READLINE_PATH = $(HOME)/homebrew/Cellar/readline/8.2.10/
endif

INCLUDES = ./includes -I$(READLINE_PATH)/include

LIBFT = ./includes/libft

LFLAGS = -lreadline -lhistory -L$(READLINE_PATH)/lib

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@make -C $(LIBFT)
	@gcc $(CFLAGS) $(LFLAGS) -o $(NAME) $(MY_OBJECTS) $(LIBFT)/libft.a
	@echo "$(C_GREEN)$(NAME) compiled with $(C_BPURP)$(CFLAGS)$(C_END)"
	@echo "$(C_RED)Welcome in our mini hell$(C_END)"
	@echo "$(C_GREEN)****      ***   *******   *****    ***   ******** $(C_END)$(C_BLUE)                 $(C_RED)***     ***    *********   ****        ***         $(C_END)"
	@echo "$(C_GREEN)*--**    *+-*   ***-***   *---**   *-*   ***+-*** $(C_END)$(C_BLUE)                 $(C_RED)*-*     *-*    *-*******   *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-++*   **--*     *-*     *-+****  *-*      *-*   $(C_END)$(C_BLUE)        |        $(C_RED)*-*     *-*    *-*         *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-* ** **-*-*     *-*     *-*  *** *-*      *-*   $(C_END)$(C_BLUE)     |  |  |     $(C_RED)*-*******-*    *-*******   *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-* ***** *-*     *-*     *-*   ****-*      *-*   $(C_END)$(C_BLUE)     |  |  |     $(C_RED)*-*******-*    *-*******   *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-*  ***  *-*     *-*     *-*    **--*      *-*   $(C_END)$(C_BLUE)  |  |  |  |  |  $(C_RED)*-*     *-*    *-*         *--*        *-*         $(C_END)"
	@echo "$(C_GREEN)*-*       *-*   ***-***   *-*     **-*   ***+-*** $(C_END)$(C_BLUE)  |  |  |  |  |  $(C_RED)*-*     *-*    *-*******   *--*******  *-********  $(C_END)"
	@echo "$(C_GREEN)***       ***   *******   ***      ***   ******** $(C_END)$(C_BLUE)  |  |  |  |  |  $(C_RED)***     ***    *********   **********  **********  $(C_END)"
	@echo "                                                    $(C_BLUE)|  |     |  |   	                   "
	@echo "                                                    $(C_BLUE)|           |                 "
	@echo "$(C_GREEN)                                                         *****                                                        $(C_END)"  
	@echo "$(C_GREEN)                                                        ********                                                      $(C_END)"  
	@echo "$(C_GREEN)                                                  ***   *-*   ***                                                     $(C_END)"  
	@echo "$(C_GREEN)                                                  .**   ****   *                                                     $(C_END)"  
	@echo "$(C_GREEN)                                                   ***   *-*                                                       $(C_END)"  
	@echo "$(C_GREEN)                                                    *** **-*    	*                                                      $(C_END)"  
	@echo "$(C_GREEN)                                 .      *       .    *******        * *   .$(C_END)"

%.o:	%.c
	@gcc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

add:
	git add Makefile src includes main.c .gitignore

clean:
	@rm -rf $(MY_OBJECTS)
	@make -C $(LIBFT) clean
	@rm -rf ./includes/ee/*.sh
	@echo "$(C_RED)$(NAME) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)/libft.a
	@echo "$(C_RED)Update: Herobrine has been removed.$(C_END)"

re: fclean all

.PHONY: all clean fclean re