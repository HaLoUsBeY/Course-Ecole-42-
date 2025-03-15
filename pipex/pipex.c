#include "pipex.h"




int main (int argc, char* argv[], char *envp[])
{
    if (argc >= 5)
    {
        int opi = open(argv[1], O_RDONLY); // şuan veriyi almak adına file desc no su aldım . bu numaradan read ile okuma yapıp ardından argv2 ve 3 teki komutları uygulayacam
        if (opi == -1)
            perror();
        
        
    }
    return (0);
}