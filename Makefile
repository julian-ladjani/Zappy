##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## 	makefile
##

make:
	@printf "%b" "\033[1;32mMake Server $(NAME)\033[0m\n";
	@make -f ./Makefile.server all;
	@printf "%b" "\033[1;32mMake Client $(NAME)\033[0m\n";
	@make -f ./Makefile.ai all

zappy_server:
	@printf "%b" "\033[1;32mMake Server $(NAME)\033[0m\n";
	@make -f ./Makefile.server re

zappy_ai:
	@printf "%b" "\033[1;32mMake Client $(NAME)\033[0m\n";
	@make -f ./Makefile.ai re

all:
	@printf "%b" "\033[1;32mMake Server $(NAME)\033[0m\n";
	@make -f ./Makefile.server all;
	@printf "%b" "\033[1;32mMake Client $(NAME)\033[0m\n";
	@make -f ./Makefile.ai all

clean:
	@printf "%b" "\033[1;32mMake Server Clean Rule $(NAME)\033[0m\n";
	@make -f ./Makefile.server clean;
	@printf "%b" "\033[1;32mMake Client Clean Rule $(NAME)\033[0m\n";
	@make -f ./Makefile.ai clean

fclean:
	@printf "%b" "\033[1;32mMake Server Fclean Rule $(NAME)\033[0m\n";
	@make -f ./Makefile.server fclean;
	@printf "%b" "\033[1;32mMake Client Fclean Rule $(NAME)\033[0m\n";
	@make -f ./Makefile.ai fclean

re:
	@printf "%b" "\033[1;32mMake Server Re Rule $(NAME)\033[0m\n";
	@make -f ./Makefile.server re;
	@printf "%b" "\033[1;32mMake Client Re Rule $(NAME)\033[0m\n";
	@make -f ./Makefile.ai re

.PHONY: all clean fclean re zappy_ai zappy_server

