/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:09:48 by gusousa           #+#    #+#             */
/*   Updated: 2022/06/30 09:23:13 by gusousa          ###   ########.fr       */
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

static void	clean(char *str, int pos)
{
	int	j;
	
	j = 0;
	while (str[pos])
		str[j++] = str[pos++];
	str[j] = '\0';
}

static char *ft_strdup(char *line, char *src, int len_stash)
{
	char	*new;

	new = malloc(len_stash + 1);
	if (!new)
		return (0);
	ft_strlcpy(new, src, len_stash + 1);
	free(line);
	clean(src, len_stash);
	return (new);
}

static char	*ft_append(char *line, char *s2, int len_stash)
{
	char	*new;
	int		line_len;

	line_len = 0;
	while (line[line_len])
		line_len++;
//	line_len = ft_strlen(line);//Se quiser pode substituir isso por uma estática.
	new = malloc(line_len + len_stash + 1);
	if (!new)
		return (0);
	ft_strlcpy(new, line, line_len + 1);
	ft_strlcpy(&new[line_len], s2, len_stash + 1);
	clean(s2, len_stash);
	free(line);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			nbyte;
	int			end_flag;
	int			len_stash;

	if (!stash)
		stash = calloc(BUFFER_SIZE + 1, 1);//Fazer a função aquiii
	line = 0;
	line = calloc(BUFFER_SIZE + 1, 1);
	end_flag = 1;
	while (1)
	{
		if (stash[0] != '\0')
		{
			len_stash = ft_strlen(stash, &end_flag);
			line = ft_strdup(line, stash, len_stash);
			if (end_flag)
				return (line);
		}
		nbyte = read(fd, stash, BUFFER_SIZE);
		stash[nbyte] = '\0';
		// Has read something.
		if (nbyte > 0)
		{
			len_stash = ft_strlen(stash, &end_flag);
			if (line[0] == '\0')
				line = ft_strdup(line, stash, len_stash);
			else
				line = ft_append(line, stash, len_stash);
			if (end_flag)
				return (line);
		}
		else
			return (line);
	
	}
}
