CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo

SRCS_DIR = ./srcs/
SRCS_FILES = philo.c check.c utils.c init.c forks.c threads.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(SRCS_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

PHILO_INCLUDE = -I./include
PHILO_INCLUDE_FILE = ./include/philo.h

all: $(NAME)

$(NAME): $(OBJS) $(PHILO_INCLUDE_FILE)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:$(SRCS_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(PHILO_INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
