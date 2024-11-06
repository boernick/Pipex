NAME = pipex
NAME_NEW = pipex_new
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/pipex_utils.c srcs/pipex.c
SRCS_NEW = srcs/pipex_utils_new.c srcs/pipex_new.c
OBJS = $(SRCS:.c=.o)
OBJS_NEW = $(SRCS_NEW:.c=.o)
HEADER = pipex.h
HEADER_NEW = pipex_new.h

PRINTF_DIR = includes/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
LIBFT_DIR = includes/Libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I $(PRINTF_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(PRINTF) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -c $< -o $@

$(LIBFT): 
	make -C $(LIBFT_DIR) bonus

$(PRINTF): $(LIBFT)
	make -C $(PRINTF_DIR)

new: $(NAME_NEW)

$(NAME_NEW): $(OBJS_NEW) $(PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_NEW) $(PRINTF) $(LIBFT) -o $(NAME_NEW)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_NEW)
	make -C $(PRINTF_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_NEW)
	make -C $(PRINTF_DIR) fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re new
