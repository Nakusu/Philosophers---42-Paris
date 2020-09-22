NAME	= philo_two

LOCA1 	= srcs/

LOCA2	= includes/

SRCS	= 	${LOCA1}main.c \
			${LOCA1}utils.c \
			${LOCA1}utils2.c \
			${LOCA1}end.c \
			${LOCA1}ft_messages.c \
			${LOCA1}time.c \
			${LOCA1}init.c \
			${LOCA1}monitoring.c

RM		= rm -f

$(CC)	= gcc

CFLAGS	= -Wall -Wextra -Werror -I ${LOCA2} -o ${NAME}

$(NAME): 
			${CC} ${CFLAGS} ${SRCS} -lpthread

all:		${NAME}

clean:
			${RM} ${NAME}

fclean :	clean

re:			fclean all

.PHONY:		all clean fclean re