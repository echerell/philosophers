CC = gcc
#DEBUG = -g -fsanitize=leak -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
THREAD_FLAG = -pthread
NAME = philo_bonus

SRCS_DIR = ./srcs/
SRCS_FILES = philo_bonus.c check.c init.c utils.c childs.c ft_itoa.c cycle.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(SRCS_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

PHILO_INCLUDE = -I./include
PHILO_INCLUDE_FILE = ./include/philo_bonus.h

all: $(NAME)

$(NAME): $(OBJS) $(PHILO_INCLUDE_FILE)
	$(CC) $(THREAD_FLAG) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:$(SRCS_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(PHILO_INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
