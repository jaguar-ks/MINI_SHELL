# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 19:14:08 by faksouss          #+#    #+#              #
#    Updated: 2023/03/10 09:08:13 by faksouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -Wall -Wextra -Werror 

LDFLAGS = /usr/lib/x86_64-linux-gnu/libreadline.a

MN_H = main/inc/mini_shell.h

RM = rm -rf

NAME = minishell

M_F = mini_shell.c

P_F = check_redirection.c\
		check_syntax.c\
		take_dollar.c\
		take_env.c\
		split_by_pp_and_rdrct.c\
		split_by_space.c\
		lexer.c\
		remove_quotes.c\

E_F =   convert_env_list_to_char.c\
			execute_all.c\
			get_needed_info.c\
			take_cmd_and_prts.c\
			take_cmd_by_cmd.c\
			take_cmd_path.c\
			take_in_rdrct.c\
			take_out_rdrct.c\

B_F = check_built.c\
		my_echo.c\
		my_cd.c\
		my_pwd.c\
		my_env.c\
		my_exit.c\
		my_unset.c\
		my_export.c\
		export_sub_fncts.c\

O_D = obj

M_D = main/src

P_D = parsing/src

E_D = execution/src

B_D = built/src

O_M = $(addprefix $(O_D)/,$(M_F:.c=.o))

O_P = $(addprefix $(O_D)/,$(P_F:.c=.o))

O_E = $(addprefix $(O_D)/,$(E_F:.c=.o))

O_B = $(addprefix $(O_D)/,$(B_F:.c=.o))

M_S = $(addprefix $(M_D)/,$(M_F))

P_S = $(addprefix $(P_D)/,$(P_F))

E_S = $(addprefix $(E_D)/,$(E_F))

B_S = $(addprefix $(B_D)/,$(B_F))

PRS_H = parsing/inc/parsing.h

EXC_H = execution/inc/execution.h

BLT_H = built/inc/built.h

LIBTOOL = libtool/libft.a

all: start $(O_D) $(NAME)

start:
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

$(O_D):
	mkdir $@

$(NAME): $(O_M) $(O_P) $(O_E) $(O_B) $(LIBTOOL)
	cc $(FLAG) $^ -lreadline -o $@
	printf "\r\033[0;33mMINISHELL is ready to lunch enjoy 😉\033[0m\n"

$(LIBTOOL):
	@printf "\r\033[0;33m⏳ libtool is compiling ...\033[0m"
	@make -C libtool

$(O_D)/%.o: $(M_D)/%.c $(MN_H)
	@printf "\r\033[0;33m⏳ main is compiling ...\033[0m"
	@printf "\r\033[0;33m compiling\033[0m %s " $<
	@cc $(FLAG) -c $< -o $@

$(O_D)/%.o: $(P_D)/%.c $(PRS_H)
	@printf "\r\033[0;33m⏳ parsing is compiling ...\033[0m"
	@printf "\r\033[0;33m compiling\033[0m %s " $<
	@cc $(FLAG) -c $< -o $@

$(O_D)/%.o: $(E_D)/%.c $(EXC_H)
	@printf "\r\033[0;33m⏳ execution is compiling ...\033[0m"
	@printf "\r\033[0;33m compiling\033[0m %s " $<
	@cc $(FLAG) -c $< -o $@

$(O_D)/%.o: $(B_D)/%.c $(BLT_H)
	@printf "\r\033[0;33m⏳ builtin is compiling ...\033[0m"
	@printf "\r\033[0;33m compiling\033[0m %s " $<
	@cc $(FLAG) -c $< -o $@

clean: 
	@printf "\r\033[0;33mclearing object files 🚮🗑️ ...\033[0m"
	@make -C libtool clean
	$(RM) $(O_D)

fclean: clean
	@printf "\r\033[0;33mYOU DELETED MY MINISHELL 😱 YOU !*#^&# 😡🤬\033[0m\n"
	@make -C libtool fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re

.SILENT: all clean fclean re $(NAME) $(O_D) $(LIBTOOL) start
