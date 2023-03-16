#include "scp.h"

void	read_conf(t_arr *arr)
{
	int	fd;
	int	j;
	int	i;

	fd = arr->conf_fd;
	while (TRUE)
	{
		arr->rd = get_next_line(fd);
		if (arr->rd == NULL)
			break ;
		// printf("%s", arr->rd);
		if (strstr(arr->rd, "#ENV") != NULL)
		{
			j = 0;
			while (strstr(arr->rd, "#END") == NULL)
			{
				arr->rd = get_next_line(fd);
				if (arr->rd[0] != '\n' && strstr(arr->rd, "#END") == NULL)
				{
					i = 0;
					while (arr->rd[i] == ' ' || arr->rd[i] == '-')
						i++;
					arr->temp = ft_split(arr->rd + i, '=');
					arr->env0[j] = ft_strschr(arr->temp[0], '\n');
					arr->env1[j] = ft_strschr(arr->temp[1], '\n');
					arr->env1[j] = ft_strschr(arr->env1[j], '\"');
					j++;
				}
			}
			// printf("\n%s", arr->rd);
		}
		if (strstr(arr->rd, "#FLAG") != NULL)
		{
			j = 0;
			while (strstr(arr->rd, "#END") == NULL)
			{
				arr->rd = get_next_line(fd);
				if (arr->rd[0] != '\n' && strstr(arr->rd, "#END") == NULL)
				{
					i = 0;
					while (arr->rd[i] == ' ' || arr->rd[i] == '-')
						i++;
					arr->temp = ft_split(arr->rd + i, '=');
					arr->flag0[j] = ft_strschr(arr->temp[0], '\n');
					arr->flag1[j] = ft_strschr(arr->temp[1], '\n');
					arr->flag1[j] = ft_strschr(arr->flag1[j] , '\"');
					j++;
				}
			}
			// printf("\n%s", arr->rd);
		}
	}
}

void	draw_help(t_arr *arr)
{
	int	i;

	i = 0;
	while (arr->flag0[i])
	{
		printf("-%s ", arr->flag0[i]);
		printf("%s", arr->flag1[i]);
		if (arr->flag0[i + 1])
			printf("\n");
		i++;
	}
	printf("\n----------------------------------------\n");

}

//str = src/dest flag = new string flag (asdfg)
void	handling_flag(t_arr *arr, char **str, char *flag)
{
	int	i;

	i = 0;
	while (arr->flag0[i])
	{
		if (strstr(flag, arr->flag0[i]) != NULL)
		{
			if (strstr(arr->flag1[i], "quit") != NULL)
			{
				arr->src = ft_sfree(arr->src);
				arr->dest = ft_sfree(arr->dest);
				printf("\n----------------------------------------\n");
				printf("|                 quit                 |\n");
				printf("----------------------------------------");
				break ;
			}
			else if (strstr(arr->flag1[i], "help") != NULL)
			{
				printf("\n----------------------------------------\n");
				printf("|                 help                 |\n");
				printf("----------------------------------------\n");
				*str = ft_sfree(*str);
				draw_help(arr);
				read_input(arr);
				break ;
			}
			else if (strstr(arr->flag1[i], "server") != NULL)
			{
				if (arr->dest == NULL)
				{
					arr->cmd[3] = arr->temp[1];
					printf("%s", arr->temp[1]);
				}
				else
				{
					arr->cmd[4] = arr->temp[1];
					printf("%s", arr->temp[1]);
				}
			}
			else
			{
				*str = ft_null_strjoin(arr->flag1[i], *str);
			}
		}
		i++;
	}
}

void	read_flag(t_arr *arr, char **str)
{
	int		i;
	int		start;
	int		end;
	char	*new;

	i = 0;
	start = -1;
	end = -1;
	while ((*str)[i] == ' ')
		i++;
	if ((*str)[i] == '-')
	{
		start = i;
		while ((*str)[i])
		{
			if ((*str)[i] == ' ' && (*str)[i + 1] != '-')
			{
				end = i;
				break ;
			}
			i++;
		}
		if (start >= 0)
			end = i;
		new = ft_strschr(ft_substr(*str, start, end - start), '-');
		*str = ft_gnl_strjoin(NULL, *str + (end + 1));
		handling_flag(arr, str, new);
	}
}

void	read_input(t_arr *arr)
{
	if (arr->src == NULL)
	{
		printf("\nsource >> (-h help)\n");
		printf("~ ");
		fflush(stdout);
		arr->src = ft_strschr(get_next_line(arr->input_fd), '\n');
		read_flag(arr, &arr->src);
	}
	if (arr->src != NULL && arr->dest == NULL)
	{
		printf("%s >> destination\n", arr->src);
		printf("~ ");
		fflush(stdout);
		arr->dest = ft_strschr(get_next_line(arr->input_fd), '\n');
		read_flag(arr, &arr->dest);
	}
	if (arr->dest != NULL)
	{
		if (arr->cmd[3])
					printf("%s", arr->cmd[3]);
		printf("%s >> %s\n", arr->src, arr->dest);
		printf("\n----------------------------------------\n");
		printf("|             command send             |\n");
		printf("----------------------------------------\n");
	}
}

void	set_env(t_arr *arr)
{
	size_t	i;

	i = 0;
	while (arr->env0[i])
	{
		if (strstr(arr->env0[i], "port") != NULL)
		{
			arr->cmd[2] = arr->env1[i];
		}
		else if (strstr(arr->env0[i], "user") != NULL)
		{
			arr->temp[1] = arr->env1[i];
		}
		i++;
	}
}

void set_cmd_flag(t_arr *arr)
{
	if (isfolder(arr->src) == 1)
		arr->cmd[1] = ft_strdup("-rP");
	else
		arr->cmd[1] = ft_strdup("-P");
}

int	main(void)
{
	t_arr arr;
	arr.conf_fd = open(".conf", O_RDONLY);
	arr.input_fd = 0;
	arr.src = NULL;
	arr.dest = NULL;
	arr.cmd[0] = ft_strdup("scp");
	arr.cmd[1] = NULL;
	arr.cmd[2] = NULL;
	arr.cmd[3] = NULL;
	arr.cmd[4] = NULL;

	printf("\n----------------------------------------\n");
	printf("|               auto_scp               |\n");
	printf("----------------------------------------");

	read_conf(&arr);
	set_env(&arr);
	read_input(&arr);
	set_cmd_flag(&arr);
	printf("(%s)", arr.dest);
	if (arr.cmd[0] != NULL && arr.cmd[1] != NULL && arr.cmd[2] != NULL 
		&& arr.src != NULL && arr.dest != NULL)
	{
		arr.temp[0] = ft_strjoin(arr.cmd[0], " ");
		arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.cmd[1]);
		arr.temp[0] = ft_gnl_strjoin(arr.temp[0], " ");
		arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.cmd[2]);
		arr.temp[0] = ft_gnl_strjoin(arr.temp[0], " ");

		if (arr.cmd[3] != NULL)
		{
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.cmd[3]);
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.src);
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], " ");
		}
		else
		{
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.src);
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], " ");
		}
		
		if (arr.cmd[4] != NULL)
		{
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.cmd[4]);
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.dest);
			//arr.temp[0] = ft_gnl_strjoin(arr.temp[0], " ");
		}
		else
		{
			arr.temp[0] = ft_gnl_strjoin(arr.temp[0], arr.dest);
			//arr.temp[0] = ft_gnl_strjoin(arr.temp[0], " ");
		}
		if (arr.temp[0])
			printf("\n%s", arr.temp[0]);
		//system(arr.temp[0]);
	}
	ft_sfree(arr.temp);
	ft_sfree(arr.src);
	ft_sfree(arr.dest);

	return (0);
}