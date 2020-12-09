SRCS		=	$(addprefix srcs/, ft_check_flags.c ft_make_conversion.c ft_printf.c ft_print_elems.c)

OBJS		=	$(SRCS:.c=.o)

DUP_OBJS	=	ft_check_flags.o ft_make_conversion.o ft_printf.o ft_print_elems.o

LIBFT		=	./srcs/libft/libft.a

NAME		=	libftprintf.a

CFLAGS		=	-Wall -Wextra -Werror

CC			=	gcc

FLAGS		=	-c -Wall -Wextra -Werror

INCLUDES	=	-I./includes

OBJS = $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) bonus -C srcs/libft
			cp $(LIBFT) $(NAME)
			$(CC) $(FLAGS) $(INCLUDES) $(SRCS)
			ar -rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(MAKE) clean -C srcs/libft
			rm -f $(OBJS) $(DUP_OBJS)

fclean:		clean
			$(MAKE) fclean -C srcs/libft
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
