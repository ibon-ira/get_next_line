/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <iboiraza@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:47:45 by iboiraza          #+#    #+#             */
/*   Updated: 2024/04/16 18:37:48 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clean_list(t_list **list)
{
	t_list	*last_node;
	t_list	*next_node;
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = malloc(BUFFER_SIZE + 1);
	next_node = malloc(sizeof(t_list));
	if (buf == NULL || next_node == NULL)
		return ;
	last_node = ft_find_last_node(*list);
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[++i])
	{
		buf[j] = last_node->content[i];
		j++;
	}
	buf[j] = '\0';
	next_node->content = buf;
	next_node->next = NULL;
	ft_prepare_next_line(list, next_node, buf);
}

char	*ft_get_line(t_list *list)
{
	int		str_len;
	char	*line_string;

	if (list == NULL)
		return (NULL);
	str_len = ft_len_to_newline(list);
	line_string = malloc(str_len + 1);
	if (line_string == NULL)
		return (NULL);
	ft_strcpy(list, line_string);
	return (line_string);
}

void	ft_collect_list(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

void	ft_create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!ft_found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read || char_read == -1)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		ft_collect_list(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	t_list			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		if (list != NULL)
		{
			while (list)
			{
				tmp = list->next;
				free(list->content);
				free(list);
				list = tmp;
			}
		}
		return (NULL);
	}
	ft_create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = ft_get_line(list);
	return (ft_clean_list(&list), next_line);
}
/*
int	main()
{
	int		fd;
//	char	buf[15];
//	int		chars_read;

	fd = open("file.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
//	while ((chars_read = read(fd, buf, 5)))
	{
		buf[chars_read] = '\0';
		printf("buf %s\n", buf);
	}
}*/
/*
int	main(void)
	{
	int	fd;

	//fd = open("1char.txt", O_RDONLY );
	fd = open("file.txt", O_RDONLY);
	printf("FD=>%d\n", fd);
	printf("LINEA1=>%s", get_next_line(fd));
	printf("FD=>%d\n", fd);
	printf("LINEA2=>%s", get_next_line(fd));
	printf("FD=>%d\n", fd);
	printf("LINEA3=>%s", get_next_line(fd));
	printf("FD=>%d\n", fd);
	printf("LINEA4=>%s", get_next_line(fd));
	printf("FD=>%d\n", fd);
	printf("LINEA5=>%s", get_next_line(fd));
	printf("FD=>%d\n", fd);
	printf("LINEA6=>%s", get_next_line(fd));
	close(fd);
 	return (0);
 }*/
