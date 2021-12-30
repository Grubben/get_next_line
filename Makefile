#SRCS		= get_next_line.c get_next_line_utils.c
SRCS		= get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

RM			= rm -rf

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -D BUFFER_SIZE=1 -g


lib			= aux-funcs.a
NAME		= a.out

run			: $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) get_next_line.c $(OBJS)
				./a.out

switch		:
				mv get_next_line.c get_next_lineOLD.c
				mv overhaul.c get_next_line.c

unswitch	:
				mv get_next_line.c overhaul.c
				mv get_next_lineOLD.c get_next_line.c

bonus		:
				cp get_next_line.c get_next_line_bonus.c
				cp get_next_line_utils.c get_next_line_utils_bonus.c
				cp get_next_line.h get_next_line_bonus.h

unbonus		:
				$(RM) *bonus.*
$(lib)		: $(OBJS)
				ar rs aux-funcs.a $(OBJS)

all			: $(OBJS)


clean		:
				$(RM) $(OBJS)

fclean		: clean
				$(RM) *.out* $(lib) *.gch

re			: fclean run


.PHONY		: $(lib) $(NAME) run all bonus clean fclean re bonus unbonus
