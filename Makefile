# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecolin <ecolin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 09:22:22 by ecolin            #+#    #+#              #
#    Updated: 2022/11/20 17:03:26 by ecolin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

GARBAGE = garbage/garbage.c
GOBJ = $(GARBAGE:.c=.o)

LIBFT_DIR = Libft/
LIBFT = ft_isascii.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_atoi.c ft_isalpha.c ft_itoa.c
LPATH = $(addprefix $(LIBFT_DIR), $(LIBFT))
LOBJ = $(LPATH:.c=.o)

SRC_DIR = src/
SRC = parsing.c cmd.c type.c pipe.c expand.c redirection.c heredoc.c error.c export_unset.c main.c echo.c export_parsing.c signal.c utils.c expand_replace.c env.c cd.c exit.c new_lst.c char.c argument.c count.c
SPATH = $(addprefix $(SRC_DIR), $(SRC))
SOBJ = $(SPATH:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SOBJ) $(LOBJ) $(GOBJ)
		@echo "$(_PURPLE_)Compiling ...$(_WHITE_)"
		$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline
		@echo "$(_MEGAWHITE)minishell ✔️$(_WHITE_)"

clean:
	$(RM) $(SOBJ) $(LOBJ) $(GOBJ)
	@echo "$(_RED_)[minishell] object files deleted.$(_WHITE_)"

fclean: clean
	/bin/rm -rf $(NAME)
	@echo "$(_RED_)[minishell] binary file deleted.$(_WHITE_)"

re: fclean all

# ~~~~~~~~~~~~~~~ COLOR ~~~~~~~~~~~~~~~~~~~ #
_GREEN_=\033[0;32m
_WHITE_=\033[0;37m
_MEGAWHITE=\033[1;37m
_YELLOW_=\033[1;33m
_PURPLE_=\033[0;35m
_CYAN_=\033[1;36m
_RED_=\033[0;31m
