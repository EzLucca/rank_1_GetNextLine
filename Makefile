
NAME = getnextline.a

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line.c get_next_line_utils.c 

BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

# MEMORY = -g -fsanitize=address,undefined

C_OBJECTS = $(SRCS:.c=.o)
.SECONDARY: ${C_OBJECTS}

all: $(NAME)

$(NAME): $(C_OBJECTS)
	ar rcs $@ $^

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(C_OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

# Used for testing
test: 
	@cc $(SRCS) main.c
	@./a.out lord.txt
	@rm -f a.out

testbonus: 
	@cc $(BONUS_SRCS) main.c
	@./a.out lord.txt rings.txt
	@rm -f a.out

# Use with gdb
gdbtest: 
	cc $(SRCS) -g main.c

gdbtestbonus: 
	cc $(BONUS_SRCS) -g main.c

# Used for memory testing
valgrindtest:
	@cc $(SRCS) -g main.c
	@valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out lord.txt
	@rm -f ./a.out 
	
valgrindtestbonus:
	@cc $(BONUS_SRCS) -g main.c
	@valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out lord.txt rings.txt
	@rm -f ./a.out 

.PHONY: all clean fclean re bonus test testbonus gdbtest gdbtestbonus valgrindtest valgrindtestbonus
