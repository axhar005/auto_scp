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
	printf("\n-----------------------------\n");
	while (arr->flag0[i])
	{
		printf("-%s ", arr->flag0[i]);
		printf("%s", arr->flag1[i]);
		if (arr->flag0[i + 1])
			printf("\n");
		i++;
	}
}

//str = src/dest flag = new string flag (asdfg)
void handling_flag(t_arr *arr, char **str, char *flag)
{
	int i;
	int j;

	i = 0;
	while (strstr(flag, arr->flag0[i]) != NULL)
	{
		if (strstr(arr->flag0[i], "h") != NULL)
		{
			*str = ft_sfree(flag);
			draw_help(arr);
			read_input(arr);
			break;
		}
		else if (strstr(arr->flag0[i], "q") != NULL)
		{
			*str = ft_sfree(flag);
			break;
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
	if (ft_strlen(arr->src) == 0)
	{
		printf("\n-----------------------------\n");
		printf(">> source (-h help):\n");
		arr->src = ft_strschr(get_next_line(arr->input_fd), '\n');
		read_flag(arr, &arr->src);
	}
	
	if (ft_strlen(arr->src) != 0)
	{
		printf("%s >> destination\n", arr->src);
		arr->dest = ft_strschr(get_next_line(arr->input_fd), '\n');
		printf("%s >> %s\n", arr->src, arr->dest);
		printf("-----------------------------\n");
		read_flag(arr, &arr->dest);
	}
}

int main(void)
{
	t_arr arr;
	arr.conf_fd = open(".conf", O_RDONLY);
	arr.input_fd = 0;

	read_conf(&arr);
	read_input(&arr);
	/*arr.src = "-hgf bobinette";
	read_flag(&arr, arr.src);*/
	
	return (0);
}