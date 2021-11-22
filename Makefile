#SRCS		= get_next_line.c get_next_line_utils.c
SRCS		= get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

RM			= rm -rf

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -D BUFFER_SIZE=5 -g


lib			= aux-funcs.a
NAME		= a.out

run			: $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) get_next_line.c $(OBJS)

$(lib)		: $(OBJS)
				ar rs aux-funcs.a $(OBJS)

all			: $(OBJS)


clean		:
				$(RM) $(OBJS)

fclean		: clean
				$(RM) *.out* $(lib) 

re			: fclean run


.PHONY		: $(lib) $(NAME) run all bonus clean fclean re
