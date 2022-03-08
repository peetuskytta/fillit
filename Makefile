CC = gcc

NAME = fillit

FLAGS = -Wall -Werror -Wextra

SRC = start.c\
	  primary_checks.c \
	  tetr_operations.c \
	  solve.c \
	  cleaning_functions.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft
	@$(CC) $(FLAGS) -c $(SRC)
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)

clean:
	@make -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all 
