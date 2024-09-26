NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex_utils.c pipex.c
OBJS = $(SRCS:.c=.o)
HEADER = pipex.h

PRINTF_DIR = includes/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
LIBFT_DIR = includes/Libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I $(PRINTF_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(PRINTF) $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

$(LIBFT): 
	make -C $(LIBFT_DIR) bonus

$(PRINTF): $(LIBFT)
	make -C $(PRINTF_DIR)

clean:
	rm -f $(OBJS)
	make -C $(PRINTF_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PRINTF_DIR) fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re