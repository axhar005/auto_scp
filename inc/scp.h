#ifndef SCP_H
# define SCP_H

# include "../ft_libft/inc/libft.h"
# include <ctype.h>
# include <stdio.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

// struct
//0   1    2   3                        4
//scp -P 1054 ocarre@70.53.246.206:
typedef struct s_arr
{
	char	*flag0[10000];
	char	*flag1[10000];
	char	*env0[10];
	char	*env1[10];
	char	*cmd[5];
	char	**temp;
	char	*src;
	char	*dest;
	char	*rd;
	int		input_fd;
	int		conf_fd;
}			t_arr;

// prototype
char		*ft_strschr(char *str, char c);
size_t		ft_strcnum(char *str, char c);
void		read_input(t_arr *arr);
void		read_flag(t_arr *arr, char **str);
void		handling_flag(t_arr *arr, char **str, char *flag);
void		draw_help(t_arr *arr);
void		set_env(t_arr *arr);

#endif