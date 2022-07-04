/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:09:48 by gusousa           #+#    #+#             */
/*   Updated: 2022/07/04 13:23:44 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str, int *end_flag)
{
	int	len;

	len = 0;
	*end_flag = 1;
	while (str[len])
	{
		if (str[len] == '\n')
			return (len + 1);
		len++;
	}
	*end_flag = 0;
	return (len);
}

void	ft_strlcpy(char *dst, char *src, int size)
{
	int	i;
	int	len_src;

	i = 0;
	len_src = 0;
	while (src[len_src])
		len_src++;
	while (src[i] && (i < size - 1) && i < len_src)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

static void	move_remains(char *str, int pos)
{
	int	j;

	j = 0;
	while (str[pos])
		str[j++] = str[pos++];
	str[j] = '\0';
}

static char	*ft_strdup(char *src, int len_stash)
{
	char	*new;

	new = malloc(len_stash + 1);
	if (!new)
		return (0);
	ft_strlcpy(new, src, len_stash + 1);
	move_remains(src, len_stash);
	return (new);
}

static char	*ft_append(char *line, char *s2, int len_stash)
{
	char	*new;
	int		line_len;

	line_len = 0;
	while (line[line_len])
		line_len++;
	new = malloc(line_len + len_stash + 1);
	if (!new)
		return (0);
	ft_strlcpy(new, line, line_len + 1);
	ft_strlcpy(&new[line_len], s2, len_stash + 1);
	move_remains(s2, len_stash);
	free(line);
	return (new);
}

char	*ft_calloc(size_t n_elements, size_t size)
{
	size_t	i;
	char	*str;

	if (!n_elements || !size)
	{
		n_elements = 1;
		size = 1;
	}
	str = malloc(n_elements * size);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < n_elements * size)
		str[i] = 0;
	return (str);
}

char	*divide_et_vince(int fd, char *line, char *stash)
{
	int	nbyte;
	int	end_flag;
	int	len_stash;

	end_flag = 0;
	if (stash[0] != '\0')
	{
		len_stash = ft_strlen(stash, &end_flag);
		line = ft_strdup(stash, len_stash);
	}
	while (end_flag == 0)
	{
		nbyte = read(fd, stash, BUFFER_SIZE);
		if (nbyte <= 0 && *stash == 0)
			break ;
		stash[nbyte] = '\0';
		len_stash = ft_strlen(stash, &end_flag);
		if (line == 0)
			line = ft_strdup(stash, len_stash);
		else
			line = ft_append(line, stash, len_stash);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = 0;
	line = divide_et_vince(fd, line, stash);
	return (line);
}
