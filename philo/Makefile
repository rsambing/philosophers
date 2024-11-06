CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC = $(SRCDIR)/actions_utils.c $(SRCDIR)/initialize.c $(SRCDIR)/list.c \
		$(SRCDIR)/philo_actions.c $(SRCDIR)/philo_essentials.c \
		$(SRCDIR)/philo_utils.c $(SRCDIR)/philo.c $(SRCDIR)/utils.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
NAME = philo

all: $(BINDIR)/$(NAME)


$(BINDIR)/$(NAME): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(BINDIR)/$(NAME)
	@echo "\033[1;32mCompilado com sucesso! Executável em $(BINDIR)/$(NAME)\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[1;36mCompilando: $<\033[0m"

clean:
	rm -rf $(OBJDIR)
	@echo "\033[1;31mArquivos objeto removidos.\033[0m"

fclean: clean
	rm -rf $(BINDIR)/$(NAME)
	@echo "\033[1;31mExecutável removido.\033[0m"

re: fclean all

.PHONY: all clean fclean re
