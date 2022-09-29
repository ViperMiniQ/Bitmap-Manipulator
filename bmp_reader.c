void load_rgb_data_from_txt_file(FILE *file, int width, int height, pixel *pixels)
{
    pixel pix;
    size_t read, len = 0;
    char *line;
    int *d = (int*)malloc(1);

    while((read = getline(&line, &len, file)) != -1) 
    {
        while(sscanf(line, "%06x", &pix) == 1)
        {
            pixels[*d] = pix;
            line = line + 7;  // file structure 'rrggbb rrggbb rrggbb' <- need to include the whitespace between values
            *d+=1;
        }
    }
}

BMPHeader get_bmp_file_info(FILE *image)
{
	BMPHeader bmp_header;
	fread(&bmp_header, 1, sizeof(bmp_header), image);
	return bmp_header;
}

void print_bmp_header_info(BMPHeader bmp_header)
{
    printf("\n signature = %x", bmp_header.signature);
	printf("\n size = %x", bmp_header.size);
	printf("\n reserved1 = %x", bmp_header.reserved1);
	printf("\n reserved2 = %x", bmp_header.reserved2);
	printf("\n offset = %x", bmp_header.offset);
	printf("\n dib_header_size = %x", bmp_header.dib_header_size);
	printf("\n width = %x", bmp_header.width);
	printf("\n height = %x", bmp_header.height);
	printf("\n planes = %x", bmp_header.planes);
	printf("\n bits_px = %x", bmp_header.bits_px);
	printf("\n compression = %x", bmp_header.compression);
	printf("\n image_data_size = %x", bmp_header.image_data_size);
	printf("\n horizontal_resolution_ppm = %x", bmp_header.horizontal_resolution_ppm);
	printf("\n vertical_resolution_ppm = %x", bmp_header.vertical_resolution_ppm);
	printf("\n colors = %x", bmp_header.colors);
	printf("\n important_colors = %x", bmp_header.important_colors);
}

void load_and_print_bmp_file_header(FILE *image)
{
    print_bmp_header_info(get_bmp_file_info(image));
}