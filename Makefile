# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 19:14:08 by faksouss          #+#    #+#              #
#    Updated: 2023/02/23 21:19:40 by faksouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -Wall -Wextra -Werror 

INC = main/inc/mini_shell.h

RM = rm -rf

NAME = minishell

S_F = mini_shell.c

O_D = obj

S_D = main/src

OBJ = $(addprefix $(O_D)/,$(S_F:.c=.o))

SRC = $(addprefix $(S_D)/,$(S_F))

PRS = parsing/parsing.a

LIBTOOL = libtool/libft.a

all: start $(O_D) $(NAME)

start:
	printf "\r"
	echo "   _______         _          ______         _      _         _         _______   "
	echo "  |*******|       /*\        /******\       |*|    |*|       /*\       |*******\  "
	echo "   --|*|--       /*-*\      |*|----|*|      |*|    |*|      /*-*\      |*|----|*| "
	echo "     |*|        /*/_\*\     |*|   _______   |*|    |*|     /*/_\*\     |*|____|*| "
	echo " _   |*|       /*******\    |*|  |*******|  |*|    |*|    /*******\    |*******/  "
	echo "|*|__|*|      /*/-----\*\   |*|___-|*|-|*|  |*\____/*|   /*/-----\*\   |*|--\*\   "
	echo " \*****/     /*/       \*\   \******/   -    \******/   /*/       \*\  |*|   \*\  "
	echo "   ---       --         --    ------          ------    --         --   -     --  \n"
	echo "          :~-._                                                 _.-~:       "
	echo "          : :.~^o._        ________---------________        _.o^~.:.:       "
	echo "          : ::.'?88booo~~~.::::::::...::::::::::::..~~oood88P'.::.:         "
	echo "          :  ::: '?88P .:::....         ........:::::. ?88P' :::. :         "
	echo "           :  :::. '? .::.            . ...........:::. P' .:::. :          "
	echo "            :  :::   ... ..  ...       .. .::::......::.   :::. :           "
	echo "            '  :' .... ..  .:::::.     . ..:::::::....:::.  ': .'           "
	echo "              :..    ____:::::::::.  . . ....:::::::::____  ... :           "
	echo "             :... ':~    ^~-:::::..  .........:::::-~^    ~::.::::          "
	echo "             '.::. '\   \033[0;31m(8)\033[0m  \b:::..::.:.:::::::d/  \033[0;31m(8)\033[0m     /'.::::'          "
	echo "              ::::.  ~-._v  |b.::::::::::::::d|      v_.-~..:::::             "
	echo "              '.:::::... ~~^?888b..:::::::::::d888P^~...::::::::'           "
	echo "               '.::::::::::....~~~ .:::::::::~~~:::::::::::::::'            "
	echo "                '..:::::::::::   .   ....::::    ::::::::::::,'             "
	echo "                  '. .:::::::    .      .::::.    ::::::::'.                "
	echo "                    '._ .:::    .        :::::.    :::::_.'                 "
	echo "                       '-. :    .        :::::      :,-'                    "
	echo "                          :.   :___     .:::___   .::                       "
	echo "                ..--~~~~--:+::. ~~^?b..:::dP^~~.::++:--~~~~--..             "
	echo "                  ___....--'+:::.    '~8~'    .:::+'--....___               "
	echo "                ~~   __..---'_=:: ___gd8bg___ :==_'---..__   ~~             "
	echo "                 -~~~  _.--~~'-.~~~~~~~~~~~~~~~,-' ~~--._ ~~~-              "
	echo "                    -~~            ~~~~~~~~~   _ Seal _  ~~-                \n\n"

$(O_D):
	mkdir $@

$(NAME): $(OBJ) $(PRS) $(LIBTOOL)
	cc $(FLAG) -lreadline $^ -o $@
	printf "\r MINISHELL is ready to lunch enjoy 😉\n"

$(PRS):
	printf "\r ⏳ parsing is compiling ..."
	make -C parsing

$(LIBTOOL):
	printf "\r ⏳ libtool is compiling ..."
	make -C libtool

$(O_D)/%.o: $(S_D)/%.c $(INC)
	@cc $(FLAG) -c $< -o $@

clean:
	printf "\r clearing object files 🚮🗑️ ..."
	make -C libtool clean
	make -C parsing clean
	$(RM) $(O_D)

fclean: clean
	printf "\r YOU DELETED MY MINISHELL 😱 YOU !*#^&# 😡🤬\n"
	make -C libtool fclean
	make -C parsing fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re

.SILENT: all clean fclean re $(NAME) $(O_D) $(PRS) $(LIBTOOL) start

