#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int main()
 {
     int fd;
	char	*str;
	int i = 0;

	fd = open("teste1.txt", O_RDONLY, 0);
    ///do
	while (i++ < 11)
	{
		str = get_next_line(fd);   	
		//free(str);
    	printf("%s", str);
	}
	 close(fd);
     return (0);
 }
 
