#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    long long time1 = time(NULL);
    char command[256];
    FILE *pMainfile = fopen(argv[1], "r");
    if (argv[1] == NULL)
    {
        printf("\nno files given compiletion ended");
        return 1;
    }

    char buffer[256];
    sprintf(command, "gcc %s -o %s", argv[1], argv[2]);
    // file reader
    int k = 0;
    while (fgets(buffer, 256, pMainfile) != NULL)
    {
        k += 1;
        if (k >= 100)
        {
            break;
        }

        char buffbuff[8];
        // makes buffbuff
        for (int i = 0; i < 8; i++)
        {
            buffbuff[i] = buffer[i];
        }
        // sees if line has include
        buffbuff[strcspn(buffbuff, "\r\n")] = 0;
        if (strncmp(buffbuff, "#include", 8) == 0)
        {
            // cheeks for if line doesnt have a C stanard
            // lib
            int i = 9;
            char lib[128] = " ";
            while (buffer[i - 1] != '>')
            {
                lib[i - 9] = buffer[i];
                i += 1;
            }
            // checks if there is a lib that matchs
            // the lib on the cerrant line if there is
            // then it takes the command for lib and adds it
            // to the gcc compiler command line command
            char line[362] = "hello";
            i = 0;
            char temp_command[256] = "";
            char libkey[128] = "";
            FILE *pLib = fopen("C:\\Users\\Administrator\\OneDrive\\Desktop\\C\\gcc_wappper\\libpath.txt", "r");
            rewind(pLib);
            while (fgets(line, 362, pLib) != NULL)
            {
                // gets libkey
                i = 0;
                while (line[i] != ':')
                {
                    libkey[i] = line[i];
                    i += 1;
                }
                // gets the command
                if (strcmp(lib, libkey) == 0)
                {
                    while (line[i - 1] != ';')
                    {
                        temp_command[i - strlen(libkey)] = line[i + 1];
                        i += 1;
                    }
                    temp_command[strlen(temp_command) - 2] = '\0';
                    i = 0;
                    break;
                }
                strcpy(libkey, " ");
            }
            fclose(pLib);
            strcat(command, " ");
            strcat(command, temp_command);
            printf("\n%s was%sfound\n", lib, (i == 0) ? " " : " not ");
        }
    }
    printf("\ncommand is %s", command);
    system(command);
    fclose(pMainfile);
    printf("\n\nit toke %d", time(NULL) - time1);

    return 0;
}
