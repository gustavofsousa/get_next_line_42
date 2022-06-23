
#include <stdlib.h>

static size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

static size_t	ft_strlcpy(char *dst, char *src, int len)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!len)
		return (src_len);
	i = -1;
	while (src[++i] && (i < len - 1) && (i < src_len))
	{
		dst[i] = src[i];
	}
	dst[i] = 0;
	return (src_len);
}

static char	*ft_strdup(char *s)
{
	char	*my_copy;
	size_t	len;

	len = ft_strlen(s);
	my_copy = malloc(len + 1);
	if (!my_copy)
		return (NULL);
	ft_strlcpy(my_copy, s, len + 1);
	return (my_copy);
}

static char	*ft_join(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;
	
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);//Ou \n com strrchr;
	ft_strlcpy(new, s1, s1_len + 1); //Falta malloc;
	ft_strlcpy(&new[s1_len], s2, //algo);
	free(str)
}
