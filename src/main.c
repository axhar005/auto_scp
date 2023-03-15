#include "scp.h"

void read_conf(t_arr *arr)
{
	int fd;
	int j;
	int i;

	fd = arr->conf_fd;
	while (TRUE)
	{
		arr->rd = get_next_line(fd);
		if (arr->rd == NULL)
			break;
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
					j++;
				}
			}
			// printf("\n%s", arr->rd);
		}
	}
}

void draw_help(t_arr *arr)
{
	int i;

	i = 0;
	printf("\n-------------Help-------------\n");
	while (arr->flag0[i])
	{
		printf("-%s ", arr->flag0[i]);
		printf("%s", arr->flag1[i]);
		if (arr->flag0[i + 1])
			printf("\n");
		i++;
	}
	printf("\n------------------------------\n");
}

//str = src/dest flag = new string flag (asdfg)
void handling_flag(t_arr *arr, char **str, char *flag)
{
	int i;

	i = 0;
	while (arr->flag0[i])
	{
		if (strstr(flag, arr->flag0[i]) != NULL)
		{
		printf("a");
			if (strstr(arr->flag1[i], "quit") != NULL)
			{
				arr->src = ft_sfree(arr->src);
				arr->dest = ft_sfree(arr->dest);
				printf("------------------------------\n");
				break;
			}
			else if (strstr(arr->flag1[i], "\"help\"") != NULL)
			{
				*str = ft_sfree(*str);
				draw_help(arr);
				read_input(arr);
				break;
			}
			else if (strstr(arr->flag1[i], "\"server\"") != NULL)
			{
				if (arr->src != NULL)
					arr->src = ft_gnl_strjoin(arr->cmd[3], arr->src);
				else
					arr->src = arr->cmd[3];
			}
			else
			{
				*str = ft_gnl_strjoin(*str, arr->flag1[i]);
			}
		}
		i++;
	}	
}


void read_flag(t_arr *arr, char **str)
{
	int i;
	int start;
	int end;
	char *new;

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
				break;
			}
			i++;
		}
		if (start >= 0)
			end = i;
		new = ft_strschr(ft_substr(*str, start, end - start), '-');
		*str = ft_gnl_strjoin(NULL, *str + (end+1));
		handling_flag(arr, str, new);
	}
}


void read_input(t_arr *arr)
{
	if (arr->src == NULL)
	{
		printf("\n------------------------------\n");
		printf(">> source (-h help):\n");
		arr->src = ft_strschr(get_next_line(arr->input_fd), '\n');
		read_flag(arr, &arr->src);
	}
	
	if (arr->src != NULL && arr->dest == NULL)
	{
		printf("%s >> destination\n", arr->src);
		arr->dest = ft_strschr(get_next_line(arr->input_fd), '\n');
		read_flag(arr, &arr->dest);
	}
	if (arr->dest != NULL)
	{
		printf("%s >> %s\n", arr->src, arr->dest);		
		printf("------------------------------\n");
	}
}

void set_env(t_arr *arr)
{
	size_t i;

	i = 0;
	while(arr->env0[i])
	{
		printf("\n%s\n", arr->env0[i]);
		// if (strstr(arr->env0[i], "port") != NULL)
		// {
		// 	//arr->cmd[2] = arr->env1[i];
		// }
		// else if (strstr(arr->env0[i], "user") != NULL)
		// {
		// 	//arr->cmd[3] = arr->env1[i];
		// }
		i++;
	}
}

int main(void)
{
	t_arr arr;
	arr.conf_fd = open(".conf", O_RDONLY);
	arr.input_fd = 0;
	arr.src = NULL;
	arr.dest = NULL;
	arr.cmd[0] = ft_strdup("scp");

	read_conf(&arr);
	set_env(&arr);
	read_input(&arr);
	/*arr.src = "-hgf bobinette";
	read_flag(&arr, arr.src);*/
	
	return (0);
}