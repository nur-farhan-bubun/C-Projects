#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct args
{
    unsigned int file_count;
    char **file; // cuz string is list of characters
} Args;

void parse_args(int argc, char **argv, Args *args)
{
    args->file = malloc(argc * sizeof(char *));
    int index = 0;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
  
            printf("./main [--help] [--version] [--file <filename>]\n");
        }
        else{

            args->file[index] = argv[i];
            index++;
               
        }
        //the number of files
        args->file_count = index;
    }
}
// i want to read a file now
 void read_file(const char *filopath,char **buffer){
 int  tmp_capacity = 1024;
    int tmp_size = 0;
char *tmp_buffer = malloc(tmp_capacity *sizeof(char));
    FILE *file = fopen(filopath, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filopath);
        return;
    }
    //now i go
 int ch;
 while((ch =fgetc(file)) !=EOF){
  
     if(tmp_size>tmp_capacity){
        tmp_capacity *= 2;
      char *new_tmp_buffer = realloc(tmp_buffer, tmp_capacity * sizeof(char));
        if (new_tmp_buffer == NULL) {
                printf("Memory allocation failed\n");
                free(tmp_buffer);
                fclose(file);
                return;
            }
            tmp_buffer = new_tmp_buffer;
     }
 tmp_buffer[tmp_size] =(char)ch;//type casting
 printf("%c",tmp_buffer[tmp_size]);
 tmp_size++;
 }



//file reading is done
//now close the file
fclose(file);
//now i want to return the buffer
//now free the buffer
free(tmp_buffer);

 }


int main(int argc, char **argv)
{
    Args args={0};
    parse_args(argc, argv, &args);
    read_file(args.file[1], NULL);
    printf("Number of files: %d\n", args.file_count);
  
return 0;


}