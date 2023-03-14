# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:34:33 by oboucher          #+#    #+#              #
#    Updated: 2023/03/08 20:13:22 by oboucher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- LIBRARY NAME ---#
NAME = scp

CNAME = $(YELLOW)~ SCP ${GREEN}

#--- COMMAND VARIABLES ---#
CC = gcc

#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

RM = rm -f

AR = ar rcs

MK = mkdir -p

#--- COLORS ---#
GREEN	=	\033[1;32m

RED		=	\033[1;31m

BLUE	=	\033[1;34m

YELLOW	=	\033[1;93m

WHITE	=	\033[1;97m

RESET 	= 	\033[0m

#--- ECHO COLOR ---#
GECHO = @echo "$(GREEN)"

RECHO = @echo "$(RED)"

BECHO = @echo "$(BLUE)"

YECHO = @echo "$(YELLOW)"

WECHO = @echo "$(WHITE)"

#--- BACKGROUD ---#
BGREEN	=	\033[0;42m

BRED 	=  	\033[0;101m

BYELLOW =	\033[0;103m

BBLUE =		\033[0;104m

#--- INCLUDE ---#
INCDIR = inc

#--- SOURCE ---#
LIBFT = libft.a

LDIR = ft_libft/

SRCDIR = src

SRCS = 	main.c scp.c

VPATH	=	${SRCDIR}

#--- OBJECT ---#
OBJDIR  =   obj

OBJS = $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})

#--- RULES ---#
${OBJDIR}/%.o : %.c
	@${CC} -I${INCDIR} -I. -c $< -o $@
	
all				: 	 	pokeball libft $(NAME)
	
$(NAME)			: 		$(OBJDIR) $(OBJS)
	@${CC} -I${INCDIR} -o ${NAME} ${OBJS} ${LDIR}${LIBFT}
	@echo "$(CNAME)       sucessefully compiled 📁.${RESET}"

$(OBJDIR)		:
	@$(MK) ${OBJDIR}

libft			:
	@$(MAKE) -C $(LDIR)

pokeball		:
	clear
	$(RECHO)"              ######              "
	@echo	"           ############           "
	@echo	"          ##############          "
	@echo	"         #######  #######         "
	$(WECHO)"         #######  #######         "
	@echo	"          ##############          "
	@echo	"           ############           "
	@echo	"              ######              \n"

run 			:		all
	@./${NAME}
	
clean			:
	@$(RM) $(OBJS)
	@$(RM)r $(OBJDIR)
	@$(MAKE) -C $(LDIR) clean
	
fclean			: 		clean	
	@$(RM) $(NAME)
	@$(MAKE) -C $(LDIR) fclean
	@echo "$(CNAME) object files and executable successfully removed 🗑.${RESET}"

re				: 		fclean all

.PHONY			: 		all clean fclean re