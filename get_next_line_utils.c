/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <iboiraza@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:08:34 by iboiraza          #+#    #+#             */
/*   Updated: 2024/04/16 17:48:05 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_find_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	ft_found_newline(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	ft_len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	ft_strcpy(t_list *list, char *line_str)
{
	int	i;
	int	j;

	if (list == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				line_str[j] = '\n';
				line_str[++j] = '\0';
				return ;
			}
			line_str[j] = list->content[i];
			i++;
			j++;
		}
		list = list->next;
	}
	line_str[j] = '\0';
}

void	ft_prepare_next_line(t_list **list, t_list *next_node, char *buf)
{
	t_list	*temp;

	if (list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (next_node->content[0])
		*list = next_node;
	else
	{
		free(buf);
		free(next_node);
	}
}
