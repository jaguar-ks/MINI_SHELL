# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 18:10:27 by faksouss          #+#    #+#              #
#    Updated: 2023/03/07 02:59:32 by faksouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S_F = convert_env_list_to_char.c\
		execute_all.c\
		get_needed_info.c\
		take_cmd_and_prts.c\
		take_cmd_by_cmd.c\
		take_cmd_path.c\
		take_in_rdrct.c\
		take_out_rdrct.c\

S_D = src

O_D = obj

OBJ = $(addprefix $(O_D)/,$(S_F:.c=.o))

SRC = $(addprefix $(S_D)/,$(S_F))

FLAG = -Wall -Wextra -Werror

INC = inc/execution.h

RM = rm -rf

NAME = execution.a

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

.SILENT: all clean fclean re $(NAME) $(O_D)
