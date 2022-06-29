
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

static char *ft_strdup(char *line, char *src)
{
	char	*new;
	int		len;

	len = ft_strlen(src);
	new = malloc(len + 1);
	if (!new)
		return (0);
	ft_strlcpy(new, src, len + 1);
	free(line);
	clean(src, len);
	return (new);
}

static char	*ft_append(char *line, char *s2)
{
	char	*new;
	int		line_len;
	int		s2_len;

	line_len = ft_strlen(line);
	s2_len = ft_strlen(s2);
	new = malloc(line_len + s2_len + 1);
	if (!new)
		return (0);	
	ft_strlcpy(new, line, line_len + 1);
	ft_strlcpy(&new[line_len], s2, s2_len + 1);
	clean(s2, s2_len);
	free(line);
	return (new);
}

char	*ft_strchr(char *str, char c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			nbyte;

	if (!stash)
		stash = calloc(BUFFER_SIZE + 1, 1);
	line = 0;
	while (1)
	{
		if (!str_is_empty(stash))
		{
			line = ft_strdup(line, stash);
			if (ft_strchr(line, '\n'))
				return (line);
		}
		nbyte = read(fd, stash, BUFFER_SIZE);
		stash[nbyte] = '\0';
		// Has read something.
		if (nbyte > 0)
		{
			if (str_is_empty(line))
				line = ft_strdup(line, stash);
			else
				line = ft_append(line, stash);
			if (ft_strchr(line, '\n'))
				return (line);
		}
		else
			return (line);
	
	}
}
