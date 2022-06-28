
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

	len = 0;
	while(str[len] != '\0' && str[len - 1] != '\n')
		len++;
	return (len);
}

void	strlcpy(char *dst, char *src, int len)
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

static void	*clean(char *str, int pos)
{
	int	j;

	j = 0;
	while (str[pos])
		new[j++] = str[pos++];
	new[j] = '\0';
}

static char	*ft_strdup(char *str)
{
	char	*line;
	int		len;

	len = ft_strlen(str);//new
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	strlcpy(line, str, len);
	clean(str, len + 1);
	return (line);
}

static int		find_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}


static char	*ft_append(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlen(s1);//new
	s2_len = ft_strlen(s2);//new
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (NULL);	
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(&str[s1_len], s2, s2_len + 1);
	clean(s2);
	free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			nbyte;

	if (!stash)
		stash = malloc(BUFFER_SIZE + 1);
	line = 0;
	while (1)
	{
		// If nbyte has come from another lap.
		if (!str_is_empty(stash))
		{
			line = ft_strdup(stash);
			stash = clean(stash);
			if (find_new_line)
				return (line);
		}
		nbyte = read(fd, stash, BUFFER_SIZE);
		stash[nbyte + 1] = '\0';
		// Has read something.
		if (nbyte > 0)
		{
			if (str_is_empty(line))
				line = ft_strdup(stash);
			else
				line = ft_append(line, stash);
			stash = clean(stash);
			if (find_new_line)
				return (line);
		}
		else
			return (line);
	
	}
}
