void remove_character_from_string(char *string, char character) 
{
    char *src, *dst;
    for(src = dst = string; *src != '\0'; src++) 
    {
        *dst = *src;
        if(*dst != character)
            dst++;
    }
    *dst = '\0';
}

int rows_in_file(FILE *file)
{
    int c;
    int rows = 0;
    fseek(file, 0, SEEK_SET);
    for(c = fgetc(file); c != EOF; c = fgetc(file))
    {
        printf("%d ", c);
        if(c == '\n')
            rows++;
    }
    rows++;
    return rows;
}

int number_of_characters_in_first_row_of_file(FILE *file, int ignore_whitespace)
{
    size_t read, len = 0;
    char *line;
    if(read = getline(&line, &len, file) == -1) 
    {
        return -1;
    }
    if(ignore_whitespace)
        remove_character_from_string(line, ' ');
    return strlen(line);
}

int number_of_pixels_in_first_row_of_file(FILE *file, int ignore_whitespace)
{
    return number_of_characters_in_first_row_of_file(file, ignore_whitespace) / 6;
}


FILE* open_file_r(char *filepath)
{
    FILE *file;
    file = fopen(filepath, "r");
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* open_file_rb(char *filename)
{
    FILE *file;
    file = fopen(filename, "rb");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* open_file_a(char *filename)
{
    FILE *file;
    file = fopen(filename, "a");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE* open_file_wb(char *filename)
{
    FILE *file;
    file = fopen(filename, "wb");
    if(file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return file;
}

