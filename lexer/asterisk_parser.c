#include "parce.h"
#include <dirent.h>

void handle_astrisk(t_cmd *cmd, char *patern)
{
    DIR *dirp;
    struct  dirent *file;
    char *file_name;
    (void)patern;

    dirp = opendir(".");
    if (!dirp)
        return ;
    while (dirp)
    {
        file = readdir(dirp);
        if (!file)
            return ;
       file_name = ft_strdup(file->d_name);
    
       add_to_argv(cmd, file_name); 
    }
}