ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
SRC = malloc.c show_alloc_mem.c
OBJ = $(SRC:.c=.o)

SYMLINK = libft_malloc.so

LIBFT = @libft/Makefile
FLAGS = -Wall -Wextra -Werror -fPIC -shared 
LIB = libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "- Compiling $(NAME)..."
	@gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "- Compiled -"
	@rm $(OBJ)
	@echo "- Deleted object files" $(NONE)
	@echo "- Creating symlink"
	@ln -sf $(NAME) $(SYMLINK)
	@echo "- Symlink done"

$(LIBFT):
	@echo "- Compiling Libft ..."
	@make -s -C libft
	@echo "- Libft ready -"

$(OBJ): $(SRC)
	@echo "- Making object files..."
	@gcc $(FLAGS) -c $(SRC)

clean:
	@echo "- Removing object files..."
	@rm -rf $(OBJ)
	@make -s -C libft clean
	@echo "- Removing symlink"
	@rm -f $(SYMLINK)

fclean: clean
	@echo "- Removing $(NAME)..."
	@rm -rf $(NAME)
	@make -s -C libft fclean

re: fclean all
