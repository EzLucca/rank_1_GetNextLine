
NAME = getnextline.a

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line.c get_next_line_utils.c 

BONUS_SRCS = get_next_line_bonus.c get_next_line_utils.c

MEMORY = -g -fsanitize=address,undefined

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
	@cc $(SRCS) main.c -o output
	@./output
	@rm -f output

testbonus: 
	@cc $(BONUS_SRCS) mainbonus.c -o output
	@./output
	@rm -f output

# Use with gdb
gdbtest: 
	@cc $(SRCS) -g main.c

gdbtestbonus: 
	@cc $(BONUS_SRCS) -g mainbonus.c

# Used for memory testing
memorytest: 
	@cc $(MEMORY) $(SRCS) main.c -o output
	@./output
	@rm -f output

memorytestbonus: 
	@cc $(MEMORY) $(BONUS_SRCS) mainbonus.c -o output
	@./output
	@rm -f output
.PHONY: all clean fclean re bonus test testbonus gdbtest gdbtestbonus memorytest memorytestbonus
