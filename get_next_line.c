
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	str_is_empty(char *str)
{
	if (!str)
		return (1);
	return (*str == '\0');
}

// I'm using this to copy an intire string or part of the string (begin, end)
static char	*ft_strdup(char *str)
{
	int		i;
	char	*line;
	int		end;

	//Find where string ends
	end = 1;
	while(str[end] != '\0' && str[end - 1] != '\n')
			end++;
	// Aloccate the good size
	line = malloc(end + 1);
	if (!line)
		return (NULL);
	i = -1;
	// Does the copy.
	while (++i < end)
		line[i] = str[i];
	line[i] = '\0';
	return (line);
}

static int		find_new_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

static char	*clean(char *str)
{
	int	i;
	int	j;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	new = malloc(BUFFER_SIZE + 1);
	j = 0;
	//Check if there's a \n
	if (str[i++] == '\n')
		while (str[i])
			new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);

}

static char	*ft_append(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	s2_len = 0;
	while (s2[s2_len] && s2[s2_len - 1] != '\n')
		s2_len++;
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		str[s1_len + i] = s2[i];
	str[s1_len + i] = '\0';
	free(s1);
	return (str);
}


char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			nbyte;
	int			i_new_line;

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
			i_new_line = find_new_line(line);
			if (i_new_line != -1)
				return (line);
		}
		nbyte = read(fd, stash, BUFFER_SIZE);
		stash[nbyte + 1] = '\0';
		// Has read something.
		if (nbyte > 0)
		{
			i_new_line = find_new_line(stash);
			// If LINE is empty:
			if (str_is_empty(line))
				line = ft_strdup(stash);
			// If there's sth in line:
			else
				line = ft_append(line, stash);
			stash = clean(stash);
			if (i_new_line != -1)
				return (line);
		}
		else
			return (line);
	
	}
}
