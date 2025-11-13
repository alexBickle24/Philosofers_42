NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -g -pthread
RM = rm -rf
MKDIR = mkdir -p

SRC_FILES = main.c\
            free_and_errors.c\
            free_mutex.c\
            set_mthr.c\
            threads_mutex.c\
            time_stop.c\
            control.c\
            working.c\
            working2.c\
            working3.c

OBJ_DIR = obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)


$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
