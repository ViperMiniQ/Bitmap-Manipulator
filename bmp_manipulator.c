#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "structs.h"
#include "miscellaneous.c"
#include "bmp_reader.c"
#include "bmp_creator.c"


int menu(void)
{
	const char *arrow[5] = {" "," ",">"," "," "};
	int choice = 0;
	
	char char_input = 0;
	while(char_input != 13) // Carriage Return
	{
		if(char_input == 's' || char_input == 'S') // arrow down
		{
			choice++;
			if(choice == 3)
				choice=0;
		}
			
		if(char_input == 'w' || char_input == 'W') // arrow up
		{
			choice--;
			if(choice == -1)
				choice=2;
		}

		printf("\e[1;1H\e[2J");  // POSIX terminal clearscreen
		printf("	PLEASE CHOOSE ONE OF THE FOLLOWING: \n\n");
		printf("	Use 'w' for up, 's' for down:\n");
		printf("   %s    1.) Read .bmp file header.\n", arrow[choice + 2]);
		printf("   %s    2.) Create .bmp from txt file data.\n", arrow[choice + 1]);
		printf("   %s    3.) Exit.\n\n", arrow[choice]);
		system("/bin/stty raw");  // input is not buffered, action on keypress
		char_input = getc(stdin);
		system("/bin/stty cooked"); // return to terminal default state
	}

	return choice;  // return selection
}

void read_pause_stdin(void)
{
	getc(stdin);
	getc(stdin);
}

int main(void)
{

	int option = -1;
	char *filename = (char *)malloc(4);
	FILE *file;
	
	//menu
	while(option != 2)
	{
		if(option == 1)
        {
            printf("\n Input txt file containing pixel data: ");
            scanf("%s", filename);
			
            file = open_file_r(filename);
			
            int width = number_of_pixels_in_first_row_of_file(file, 1);
            fseek(file, 0, SEEK_SET);
            int height = rows_in_file(file);
            fseek(file, 0, SEEK_SET);
			
            pixel *pixels = malloc((height*width) * sizeof(pixel));
            load_rgb_data_from_txt_file(file, width, height, pixels);
	
	    free(filename);
	    fclose(file);
			
            printf("\nInput image filename: ");
	    
            scanf("%s", filename);
            file = open_file_wb(filename);
            write_header_to_file(width, height, file);
            dump_pixels_to_image(width, height, file, pixels);
			
            printf("\n DONE.");
			
            read_pause_stdin();
        }
	if(option == 0)
	{
	    printf("\n Input filename: ");
	    scanf("%s", filename);
	    
	    file = open_file_rb(filename);
	    load_and_print_bmp_file_header(file);
	    
	    printf("\n\nPRESS ANY KEY TO RETURN TO MENU...");
	    free(file);
	    read_pause_stdin();
	}
	    option = menu();
	}

    printf("\n");
    return 0;
}
