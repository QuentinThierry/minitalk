SRCSSERVEUR = Srcs/serveur.c Srcs/utils.c
OBJSSERVEUR = $(SRCSSERVEUR:.c=.o)
SRCSCLIENT = Srcs/client.c Srcs/utils.c
OBJSCLIENT = $(SRCSCLIENT:.c=.o)

SRCSSERVEUR_BONUS = Srcs/serveur_bonus.c Srcs/utils_bonus.c
OBJSSERVEUR_BONUS = $(SRCSSERVEUR_BONUS:.c=.o)
SRCSCLIENT_BONUS = Srcs/client_bonus.c Srcs/utils_bonus.c
OBJSCLIENT_BONUS = $(SRCSCLIENT_BONUS:.c=.o)

DEPS = Includes/serveur.h Includes/client.h 

NAME = server
NAME1 = client
NAME_BONUS = server_bonus
NAME1_BONUS = client_bonus

all: $(NAME) $(NAME1)

$(CC): gcc

$(FLAGS):
	-Wextra -Wall -Werror

$(NAME): $(OBJSSERVEUR)
	$(CC) $(FLAGS) $(SRCSSERVEUR) -o $(NAME)

$(NAME1): $(OBJSCLIENT)
	$(CC) $(FLAGS) $(SRCSCLIENT) -o $(NAME1)

$(NAME_BONUS): $(OBJSSERVEUR_BONUS)
	$(CC) $(FLAGS) $(SRCSSERVEUR_BONUS) -o $(NAME_BONUS)

$(NAME1_BONUS): $(OBJSCLIENT_BONUS)
	$(CC) $(FLAGS) $(SRCSCLIENT_BONUS) -o $(NAME1_BONUS)

bonus: $(NAME_BONUS) $(NAME1_BONUS)

clean:
	rm -f $(OBJSCLIENT) $(OBJSSERVEUR)
	rm -f $(OBJSCLIENT_BONUS) $(OBJSSERVEUR_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME1) $(NAME_BONUS) $(NAME1_BONUS)

re: fclean all

.PHONY: re fclean all clean bonus