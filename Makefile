NAME = minishell
CC = cc
CFLAGS = -g -Wall -Werror -Wextra #-fsanitize=address

SRCPATH = src/
LIBFTPATH = ./libft
SRC = 	$(addprefix $(SRCPATH),  main.c parser/utils_prep.c utils.c parser/load_tokens.c parser/content_analyse.c\
		parser/syntax.c \
		lexer/lexer.c lexer/lexer_utils1.c lexer/lexer_utils2.c parser/parser.c \
		parser/parser_utils.c parser/parser_utils_2.c parser/parser_utils_3.c \
		executer/executer.c executer/executer_redirections.c executer/input_handling.c executer/executer_utils.c expander/expander.c expander/expander_replace.c\
		expander/expander_utils.c expander/expander_utils2.c expander/expander_varinvar.c parser/get_path.c /executer/builtins/built_in.c executer/builtins/built_in_utils.c \
		executer/builtins/env.c executer/builtins/echo.c executer/builtins/echo_utils.c executer/builtins/export.c \
		executer/builtins/export_utils.c executer/builtins/unset.c executer/builtins/cd.c executer/builtins/pwd.c executer/builtins/exit.c signals.c)  
OBJ = $(addprefix _bin/,$(notdir $(SRC:.c=.o)))
DOWNLOADFOLDER = dwnlds
INCFLAG = -Iinclude -Ilibft -I$(DOWNLOADFOLDER)/readline_out/include
LINK = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline -Llibft -lft
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT) $(DOWNLOADFOLDER)
	$(CC) $(CFLAGS) $(SRC) $(INCFLAG) $(LINK) -o $(NAME)
s: $(NAME)
	./$(NAME)
clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTPATH)
fclean: clean
	rm -f ./$(NAME)
	make fclean -C $(LIBFTPATH)
re: fclean
	$(MAKE) all

$(LIBFT):
	@git submodule init libft
	@git submodule update libft
	@cd libft && make && make clean

$(DOWNLOADFOLDER):
	mkdir -p $(DOWNLOADFOLDER)
	curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz
	tar xfz $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz -C $(DOWNLOADFOLDER)
	cd $(DOWNLOADFOLDER)/readline-8.1.2; ./configure --prefix=$(PWD)/dwnlds/readline_out; cd ../../
	make -C $(DOWNLOADFOLDER)/readline-8.1.2
	make install -C $(DOWNLOADFOLDER)/readline-8.1.2

LSANLIB = /LeakSanitizer/liblsan.a
lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK += -LLeakSanitizer -llsan -lc++
lsan: fclean $(LSANLIB)
lsan: all
$(LSANLIB):
	@if [ ! -d "LeakSanitizer" ]; then git clone https://github.com/mhahnFr/LeakSanitizer.git; fi
	@$(MAKE) -C LeakSanitizer

.PHONY: all, run, clean, fclean, re