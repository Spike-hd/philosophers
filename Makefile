NAME		= philo

CC			= gcc
CFLAGS		= -Werror -Wextra -Wall

SRC			= philosophers.c errors.c init_and_parse.c lock_unlock.c monitoring.c philo_routine.c print.c time.c utils.c
OBJ			= $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(NAME) ready"

clean:
	@echo "Removing object files..."
	@rm -f $(OBJ)

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
