
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	str_is_empty(char *str)
{
	if (!str)
		return (1);
	return (*str == '\0');
}

int	ft_strlen(char *str)
{
	int	len;

	len = 1;
	while (str[len] && str[len - 1] != '\n')
		len++;
	return (len);
}

void	ft_strlcpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (src[i] && (i < len - 1) && i < ft_strlen(src))
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

static int ft_strdup(char **dst, char *src)
{
	char	*line;
	int		len;

	len = ft_strlen(src);
	line = malloc(len + 1);
	if (!line)
		return (0);
	ft_strlcpy(line, src, len + 1);
	free(*dst);
	*dst = line;
	clean(src, len);
	return (len);
}

static int	ft_append(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (0);	
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(&str[s1_len], s2, s2_len + 1);
	clean(s2, s2_len);
	free(s1);
	s1 = str;
	return (s2_len);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			nbyte;
	int			pos_new_line;

	if (!stash)
		stash = malloc(BUFFER_SIZE + 1);
	line = 0;
	while (1)
	{
		if (!str_is_empty(stash))
		{
			pos_new_line = ft_strdup(&line, stash);
			if (pos_new_line)
				return (line);
		}
		nbyte = read(fd, stash, BUFFER_SIZE);
		stash[nbyte + 1] = '\0';
		// Has read something.
		if (nbyte > 0)
		{
			if (str_is_empty(line))
				pos_new_line = ft_strdup(&line, stash);
			else
				pos_new_line = ft_append(line, stash);
			if (pos_new_line)
				return (line);
		}
		else
			return (line);
	
	}
}
