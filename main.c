#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int main()
 {
    int		fd;
	char	*str;
	int		i;

	fd = open("sonic.txt", O_RDONLY, 0);
    ///do
	i = 0;
	while (i++ < 3)
	{
		str = get_next_line(fd);   	
    	printf("%s", str);
		free(str);
	}
	 close(fd);
     return (0);
 }
 
