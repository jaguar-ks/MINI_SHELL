# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 19:14:08 by faksouss          #+#    #+#              #
#    Updated: 2023/04/10 17:54:35 by mfouadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CFLAGS := -Wall -Wextra -Werror -fsanitize=address

READ_LIB := /usr/lib/x86_64-linux-gnu/libreadline.a

RM := rm -rf

MAIN :=		main/src/mini_shell.c \
			main/src/sub_main_fncts.c \

PARSE := 	parsing/src/check_redirection.c \
			parsing/src/check_syntax.c \
			parsing/src/lexer.c \
			parsing/src/remove_quotes.c \
			parsing/src/split_by_pp_and_rdrct.c \
			parsing/src/split_by_space.c \
			parsing/src/take_dollar.c \
			parsing/src/take_env.c \
			parsing/src/wild_card.c \

EXEC :=  	execution/src/execution.c \
			execution/src/utils.c
			

SRC := $(MAIN) $(PARSE) $(EXEC)

OBJDIR := obj

OBJ := $(patsubst %, $(OBJDIR)/%, $(SRC:.c=.o))

HEADERS :=	built/inc/built.h \
			execution/inc/execution.h \
			parsing/inc/parsing.h \
			main/inc/mini_shell.h \

LIBTOOL := libtool/libft.a

all : $(NAME)

$(NAME): $(LIBTOOL) $(OBJ)
	cc $(CFLAGS) $^ -lreadline -L /Users/faksouss/.brew/opt/readline/lib -o $@
	printf "\r\033[0;33mMINISHELL is ready to lunch enjoy 😉\033[0m\n"

$(OBJDIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iexecution/inc/execution.h -c $< -o $@

$(LIBTOOL) :
	@printf "\r\033[0;33m⏳ libtool is compiling ...\033[0m"
	@make -C libtool

clean : 
	@printf "\r\033[0;33mclearing object files 🚮🗑️ ...\033[0m"
	@make -C libtool clean
	$(RM) $(OBJ)

fclean : clean
	@printf "\r\033[0;33mYOU DELETED MY MINISHELL 😱 YOU !*#^&# 😡🤬\033[0m\n"
	@make -C libtool fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: all fclean clean re

.SILENT: all clean fclean re $(NAME) $(LIBTOOL) img

img:
	clear
	printf "\r\n"
	echo "       	   :~-._                                                 _.-~:       "
	echo "       	   : :.~^o._        ________---------________        _.o^~.:.:       "
	echo "       	   : ::.'?88booo~~~.::::::::...::::::::::::..~~oood88P'.::.:         "
	echo "       	   :  ::: '?88P .:::....         ........:::::. ?88P' :::. :         "
	echo "       	    :  :::. '? .::.            . ...........:::. P' .:::. :          "
	echo "       	     :  :::   ... ..  ...       .. .::::......::.   :::. :           "
	echo "       	     '  :' .... ..  .:::::.     . ..:::::::....:::.  ': .'           "
	echo "       	       :..    ____:::::::::.  . . ....:::::::::____  ... :           "
	echo "       	      :... ':~    ^~-:::::..  .........:::::-~^    ~::.::::          "
	echo "       	      '.::. '\   \033[0;31m(8)\033[0m  \b:::..::.:.:::::::d/  \033[0;31m(8)\033[0m     /'.::::'          "
	echo "       	       ::::.  ~-._v  |b.::::::::::::::d|      v_.-~..:::::             "
	echo "       	       '.:::::... ~~^?888b..:::::::::::d888P^~...::::::::'           "
	echo "       	        '.::::::::::....~~~ .:::::::::~~~:::::::::::::::'            "
	echo "       	         '..:::::::::::   .   ....::::    ::::::::::::,'             "
	echo "       	           '. .:::::::    .     .::::.    ::::::::::'.                "
	echo "       	             '._ .:::    .  |     :::::.    :::::_.'                 "
	echo "       	                '-. :    .        :::::      :,-'                    "
	echo "       	                   :.   :___\    .:::___   .::                       "
	echo "       	         \033[0;33m..--~~~~--:\033[0m+::. ~~^?b..:::dP^~~.::++\033[0;33m:--~~~~--..\033[0m             "
	echo "       	           \033[0;33m___....--'\033[0m+:::.   \'~8~'/   .:::+\033[0;33m'--....___\033[0m               "
	echo "       	         \033[0;33m~~   __..---'\033[0m_=:: ___gd8bg___ :==_\033[0;33m'---..__   ~~\033[0m             "
	echo "       	          \033[0;33m-~~~  _.--~~'\033[0m-.~~~~~~~~~~~~~~~,-\033[0;33m' ~~--._ ~~~-\033[0m              "
	echo "       	              \033[0;33m-~~\033[0m        \ |~~~~~~~~~~~| /           \033[0;33m~~-\033[0m                "
	echo "       	                          \|  ~~~~~~~  |/                              \n"
	echo "\033[0;31m               ▄▄▄██▀▀▀▄▄▄        ▄████  █    ██  ▄▄▄       ██▀███     \033[0m" 
	echo "\033[0;31m                ▒██  ▒████▄     ██▒ ▀█▒ ██  ▓██▒▒████▄    ▓██ ▒ ██▒    \033[0m"
	echo "\033[0;31m                ░██  ▒██  ▀█▄  ▒██░▄▄▄░▓██  ▒██░▒██  ▀█▄  ▓██ ░▄█ ▒    \033[0m"
	echo "\033[0;31m             ▓██▄██▓ ░██▄▄▄▄██ ░▓█  ██▓▓▓█  ░██░░██▄▄▄▄██ ▒██▀▀█▄      \033[0m"
	echo "\033[0;31m              ▓███▒   ▓█   ▓██▒░▒▓███▀▒▒▒█████▓  ▓█   ▓██▒░██▓ ▒██▒    \033[0m"
	echo "\033[0;31m              ▒▓▒▒0   ▒▒   ▓▒█1 0▒   ▒ v▒▓▒ ▒ ▒  ▒▒   ▓▒█░░ ▒▓ ░▒▓░    \033[0m"
	echo "\033[0;31m              1 0▒1    ▒   ▒▒ 2  ?   1 h░▒░ T :   ▒   1▒ 0  0▒ d ▒r    \033[0m"
	echo "\033[0;31m              0 J ;    K   ▒   X !   &  1!1 ; |   3   L     10   Q     \033[0m"
	echo "\033[0;31m                  1        1  0      /    0           ^  Z   1         \033[0m\n"          
