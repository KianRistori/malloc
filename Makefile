ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

SRC = $(SRC_DIR)/malloc.c $(SRC_DIR)/free.c $(SRC_DIR)/realloc.c $(SRC_DIR)/show_alloc_mem.c
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

SYMLINK = libft_malloc.so

LIBFT = @libft/Makefile
LIB = libft/libft.a

FLAGS = -Wall -Wextra -Werror -fPIC -I$(INCLUDE_DIR)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "- Compiling $(NAME)..."
	@gcc $(FLAGS) -shared $(OBJ) $(LIB) -o $(NAME)
	@echo "- Compiled -"
	@echo "- Creating symlink"
	@ln -sf $(NAME) $(SYMLINK)
	@echo "- Symlink done"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "- Compiling $< to $@"
	@gcc $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "- Compiling Libft ..."
	@make -s -C libft
	@echo "- Libft ready -"

clean:
	@echo "- Removing object files..."
	@rm -rf $(OBJ_DIR)
	@make -s -C libft clean
	@echo "- Removing symlink"
	@rm -f $(SYMLINK)

fclean: clean
	@echo "- Removing $(NAME)..."
	@rm -rf $(NAME)
	@make -s -C libft fclean

re: fclean all
