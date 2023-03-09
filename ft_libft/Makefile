# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:34:33 by oboucher          #+#    #+#              #
#    Updated: 2023/03/07 23:57:28 by oboucher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- LIBRARY NAME ---#
NAME = libft.a
CNAME = $(BLUE)~ LIBFT/GNL ${GREEN}

#--- COMMAND VARIABLES ---#
CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AR = ar rcs

MK = mkdir -p

#--- COLORS ---#
GREEN	=	\033[1;32m

RED		=	\033[1;31m

BLUE	=	\033[1;34m

YELLOW	=	\033[1;93m

WHITE	=	\033[0m

#--- BACKGROUD ---#
BGREEN	=	\033[0;42m

BRED 	=  	\033[0;101m

BYELLOW =	\033[0;103m

BBLUE =	\033[0;44m

#--- INCLUDE ---#
INCDIR = inc

#--- SOURCES ---#
SRCDIR = src

SRCS = ft_atoi.c  ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdegit.c ft_isprint.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c get_next_line_utils.c

VPATH		=    ${SRCDIR}

#--- OBJECTS ---#
OBJDIR  =   obj

OBJS = $(addprefix ${OBJDIR}/, ${SRCS:%.c=%.o})

#--- RULES ---#

${OBJDIR}/%.o : %.c
	@${CC} ${CFLAGS} -I${INCDIR} -I. -c $< -o $@
	
all				: 		$(NAME)

$(NAME)			: 		$(OBJDIR) $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(CNAME) sucessefully compiled 📁.${WHITE}"

$(OBJDIR)		:
	@$(MK) $(OBJDIR)

clean			:
	@$(RM) $(OBJS)
	@$(RM)r $(OBJDIR)

fclean			: 		clean	
	@$(RM) $(NAME)
	@echo "$(CNAME) files successfully removed 🗑.${WHITE}"

re				: 		fclean all

.PHONY			: 		all clean fclean re bonus