/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <iboiraza@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:51:47 by iboiraza          #+#    #+#             */
/*   Updated: 2024/04/16 16:43:36 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	ft_create_list(t_list **list, int fd);
void	ft_collect_list(t_list **list, char *buf);
char	*ft_get_line(t_list *list);
void	ft_strcpy(t_list *list, char *line_str);
int		ft_len_to_newline(t_list *list);
int		ft_found_newline(t_list *list);
t_list	*ft_find_last_node(t_list *list);
void	ft_clean_list(t_list **list);
void	ft_prepare_next_line(t_list **list, t_list *new_node, char *buf);

#endif
