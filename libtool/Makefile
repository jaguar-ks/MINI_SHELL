# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faksouss <faksouss@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 00:28:28 by faksouss          #+#    #+#              #
#    Updated: 2023/03/11 03:31:09 by faksouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MD = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c\
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c\
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c\
		ft_strdup.c ft_striteri.c ft_strjoin.c  ft_strlcat.c ft_strlcpy.c ft_strlen.c\
		ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c\
		ft_toupper.c ft_printf.c print_functions.c ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c ft_lstdelone.c\
		ft_lstclear.c ft_lstmap.c ft_lstiter.c get_next_line.c ft_isspace.c ft_strcmp.c\

FLAGS = -Wall -Wextra -Werror -c

CC = cc

OBJ_DIR = obj

SRC_DIR = src

SRC_F = $(addprefix $(SRC_DIR)/,SRCS_MD)

OBJS_MD = $(addprefix $(OBJ_DIR)/,${SRCS_MD:.c=.o})

HEADER = inc/libft.h

NAME = libft.a

RM = rm -rf

all : $(OBJ_DIR) ${NAME}

${NAME} : ${OBJS_MD}
	ar -rc $@ ${OBJS_MD}
	printf "\r%s \033[0;33m is ready to lunch enjoy 😉\033[0m" $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c ${HEADER}
	@${CC} ${FLAGS} $< -o $@

$(OBJ_DIR) :
	mkdir $@

clean :
	printf "\r\033[0;33m🗑️🚮 Deleting object files...\033[0m"
	@${RM} $(OBJ_DIR)

fclean : clean
	printf "\r\033[0;33m🗑️🚮 Deleting \033[0m%s" $(NAME)
	@${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re

.SILENT : all clean fclean re $(NAME) $(OBJ_DIR)
