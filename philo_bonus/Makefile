NAME		= philo_bonus

CC			= gcc
CFLAGS		= -Werror -Wextra -Wall

SRC			= philo_bonus.c errors_bonus.c init_bonus.c process_routine.c monitoring_bonus.c print_bonus.c time_bonus.c utils_bonus.c
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
