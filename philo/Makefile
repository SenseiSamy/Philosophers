CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), philo.c data.c utils.c routine.c main.c mutex.c)
OBJ_DIR = obj/
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
INCLUDE_DIR = inc/
NAME = philo

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -pthread -I $(INCLUDE_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

norme:
	@norminette | grep Error

.PHONY: all clean fclean re
