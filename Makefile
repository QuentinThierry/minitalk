SRCSSERVEUR = Srcs/serveur.c Srcs/utils.c
OBJSSERVEUR = $(SRCSSERVEUR:.c=.o)

SRCSCLIENT = Srcs/client.c Srcs/utils.c
OBJSCLIENT = $(SRCSCLIENT:.c=.o)

DEPS = Includes/serveur.h Includes/client.h 

NAME = server
NAME1 = client

all: $(NAME) $(NAME1)

$(CC): gcc

$(FLAGS):
	-Wextra -Wall -Werror

$(NAME): $(OBJSSERVEUR)
	$(CC) $(FLAGS) $(OBJSSERVEUR) -o $(NAME)

$(NAME1): $(OBJSCLIENT)
	$(CC) $(FLAGS) $(SRCSCLIENT) -o $(NAME1)

clean:
	rm -f $(OBJSCLIENT) $(OBJSSERVEUR)

fclean: clean
	rm -f server client

re: fclean all

.PHONY: re fclean all clean bonus