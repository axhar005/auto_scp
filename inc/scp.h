#ifndef SCP_H
# define SCP_H

# include "../ft_libft/inc/libft.h"
# include <stdio.h>
# include <string.h>
#include <ctype.h>

# define FALSE 0
# define TRUE 1

//struct
typedef struct s_arr
{
	char	*flag0[10000];
	char	*flag1[10000];
	char	*env1[10];
	char	*env2[10];
	char	**temp;
	char	**line;
	char	*src;
	char	*dest;
	char	*rd;
	int		input_fd;
	int		conf_fd;
}			t_arr;

//prototype
char            *ft_strschr(char *str, char c);
size_t			ft_strcnum(char *str, char c);

#endif