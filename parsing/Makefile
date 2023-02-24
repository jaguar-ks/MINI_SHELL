# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 15:40:57 by faksouss          #+#    #+#              #
#    Updated: 2023/02/23 20:00:53 by faksouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S_F = check_redirection.c\
		check_syntax.c\
		parss_cmd_ln.c\
		take_dollar.c\
		take_env.c\
		take_flag.c\
		take_input.c\
		take_output.c\
		take_pipe.c\
		take_quotes.c\
		take_redirction.c\
		take_word.c\

S_D = src

O_D = obj

OBJ = $(addprefix $(O_D)/,$(S_F:.c=.o))

SRC = $(addprefix $(S_D)/,$(S_F))

FLAG = -Wall -Wextra -Werror

INC = inc/parsing.h

RM = rm -rf

NAME = parsing.a

all: $(O_D) $(NAME)

$(NAME): $(OBJ)
	ar -rc $@ $(OBJ)

$(O_D):
	mkdir $@

$(O_D)/%.o: $(S_D)/%.c $(INC)
	@cc $(FLAG) -c $< -o $@

clean:
	$(RM) $(O_D)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: all clean fclean re $(NAME) $(O_D) start
