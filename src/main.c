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
		printf("%s", arr->rd);
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
					arr->env1[j] = ft_strschr(arr->temp[0], '\n');
					arr->env2[j] = ft_strschr(arr->temp[1], '\n');
					printf("%s", arr->env1[j]);
					printf("%s", arr->env2[j]);
					j++;
				}
			}
			printf("\n%s", arr->rd);
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
					printf("%s", arr->flag0[j]);
					printf("%s", arr->flag1[j]);
					j++;
				}
			}
			printf("\n%s", arr->rd);
		}
	}
}

void	draw_help(t_arr *arr)
{
	int	i;

	i = 0;
	printf("\n-----------------------------\n");
	while (arr->flag0[i])
	{
		printf("%s %s \n", arr->flag0[i], arr->flag1[i]);
		i++;
	}
	printf("-----------------------------");
}

// void	handling_flag(t_arr *arr, char *str)
// {
//     int i;

//     while (str[i])
//     {
//         if (arr->flag1[i] == "help")
//         {
//             draw_help(&arr);
//             read_input(&arr);
//         }
//     }
    

// }

void	read_flag(t_arr *arr, char *str)
{
    int i;
    int start;
    int end;
    char *new;

    i = 0;
    start = 0;
    end = 0;
    while(str[i] == ' ')
        i++;
    if (str[i] == '-')
    {
        start = i;
        while (str[i])
        {
            if (str[i] == ' ' && str[i + 1] != '-')
            {
                end = i;
                break;
            }
        i++;
        }
    }
    new = ft_strschr(ft_substr(str, start, end - start), '-');

}

void	read_input(t_arr *arr)
{
	printf("\n-----------------------------\n");
	printf(">> source (-h help):\n");
	arr->src = ft_strschr(get_next_line(arr->input_fd), '\n');
    read_flag(arr, arr->src);
	printf("%s >> destination\n", arr->src);
	arr->dest = ft_strschr(get_next_line(arr->input_fd), '\n');
	printf("-----------------------------");
}

int	main(void)
{
	t_arr arr;
	arr.conf_fd = open(".conf", O_RDONLY);
	arr.input_fd = 0;

	read_conf(&arr);
    read_input(&arr);


	return (0);
}