# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kristori <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 12:54:12 by kristori          #+#    #+#              #
#    Updated: 2022/10/11 10:33:40 by kristori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC	= ft_isdigit.c  ft_memset.c   ft_strncmp.c \
	  ft_atoi.c     ft_isprint.c  ft_strchr.c  \
	ft_bzero.c    ft_memchr.c   ft_strjoin.c  ft_strrchr.c \
	ft_isalnum.c  ft_memcmp.c   ft_strlcat.c  ft_substr.c \
	ft_isalpha.c  ft_memcpy.c   ft_strlcpy.c  ft_tolower.c \
	ft_isascii.c  ft_memmove.c  ft_strlen.c   ft_toupper.c \
	ft_strnstr.c  ft_calloc.c  ft_strdup.c  ft_strtrim.c \
	ft_itoa.c  ft_strmapi.c  ft_striteri.c  ft_split.c \
	ft_putchar_fd.c  ft_putstr_fd.c  ft_putendl_fd.c  ft_putnbr_fd.c

OBJ	= $(SRC:.c=.o)

BONUS	= ft_lstnew.c  ft_lstadd_front.c  ft_lstsize.c  ft_lstlast.c \
        ft_lstadd_back.c  ft_lstdelone.c  ft_lstclear.c  ft_lstiter.c \
        ft_lstmap.c

OBJ_BONUS	= $(BONUS:.c=.o)

all:	$(NAME)

$(NAME) : $(SRC)
	@gcc -Wall -Werror -Wextra -c $(SRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -f $(NAME)

bonus:
	@gcc -Wall -Werror -Wextra -c $(BONUS)
	@ar rc $(NAME) $(BONUS) $(OBJ_BONUS)

re: fclean all
