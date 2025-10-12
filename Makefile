NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror 
RM = rm -rf
MKDIR = mkdir -p

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

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

all: $(LIBFT_A) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
