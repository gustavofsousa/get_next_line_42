/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:49:11 by gusousa           #+#    #+#             */
/*   Updated: 2023/05/23 10:08:34 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_strlen_gnl(char *str, int *end_flag);
char	*ft_calloc_gnl(size_t n_elements, size_t size);
char	*ft_strdup_gnl(char *src, int len_stash);
void	move_remains(char *str, int pos);
char	*get_next_line(int fd);
char	*ft_append(char *line, char *s2, int len_stash);
char	*divide_et_vince(int fd, char *line, char *stash);
char	*get_next_line(int fd);
void	ft_strlcpy_gnl(char *dst, char *src, int size);

#endif
