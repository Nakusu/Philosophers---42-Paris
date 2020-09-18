NAME	= philo_one

LOCA1 	= ./srcs/

LOCA2	= ./includes/

SRCS	= 	${LOCA1}main.c \
			${LOCA1}utils.c

SRCSBONUS = 

RM		= rm -f

$(CC)	= gcc

CFLAGS	= -Wall -Wextra -Werror -lpthread -I${LOCA2} -o ${NAME}

$(NAME): 
			${CC} ${CFLAGS} ${SRCS}

all:		${NAME}

clean:
			${RM} ${NAME}

fclean :	clean

re:			fclean all

.PHONY:		all clean fclean re