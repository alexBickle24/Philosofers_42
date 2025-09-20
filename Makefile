NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror 
RM = rm -rf
MKDIR = mkdir -p # Si ya existe no da problemas

INCLUDE_DIR = inc
LIBFT_DIR = inc/libft
LIBFT_A = $(LIBFT_DIR)/libft.a
INCLUDE_FLAG = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)
INCLUDE = $(INCLUDE_DIR)/philo.h

SRC_DIR = src/

SRC_FILES = main.c\
			debugin.c\
			free_and_errors.c\
			free_mutex.c\
			set_mthr.c\
			threads_mutex.c\
			time_stop.c\
			control.c\
			working.c\
			working2.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

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
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@$(MKDIR) $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE_FLAG) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
