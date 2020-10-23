NAME = 	philo_one

SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
INCS_PATH = ./includes/

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS_NAME= main.c utils.c clean.c messages.c init.c utils2.c monitoring.c

CC = gcc

FLAGS =	-Wall -Werror -Wextra


all: 			$(NAME)

$(NAME):	$(OBJS)
		@$(CC) -o $(NAME) $(FLAGS) $(OBJS) -lpthread
		@echo "\033[0;34mExecutable philo_one \033[0m \033[0;32m [OK] \033[0m"


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c includes/philos.h
		@mkdir -p $(OBJS_PATH)
		@gcc $(FLAGS) -o $@ -c $<

run : 
		make re
		./$(NAME)


clean:
		@rm -rf $(OBJS_PATH)
		@echo "deleted ./objs/"

fclean: clean
		@rm -rf $(NAME)
		@echo "deleted ./philo_one"

re: fclean all

.PHONY:			all clean fclean re
