void write_header_to_file(int width, int height, FILE *file)
{
	BMPHeader header;
	header.signature = 0x4d42; // <--
	header.reserved1 = 0x0000; // <--
	header.reserved2 = 0x0000; // <--
	header.offset = 0x00000036; // <-- 
	header.dib_header_size = 0x00000028; // <-- (should be 40 (DEC) or 28 (HEX))
	header.planes = 0x0001; // <--
	header.bits_px = 0x0018; // <-- (for 24-bit bitmap should be 24 (DEC) or 18 (HEX))
	header.compression = 0x00000000; // <--
	header.image_data_size = 0x00000078; // SIZE (bytes) - 54 (bytes)
	header.horizontal_resolution_ppm = 0x00000000;  // <-- (no idea)
	header.vertical_resolution_ppm = 0x00000000; // <-- (no idea)
	header.colors = 0x00000000; // <-- (not needed)
	header.important_colors = 0x00000000; // <-- (not needed)

	header.width = width;
	header.height = height;
	header.size = header.width * header.height * 0x00000004 + 0x00000036;
	header.image_data_size = header.size - 0x00000036;

	fwrite(&header, 1, sizeof(header), file);
}

void dump_pixels_to_image(int width, int height, FILE *file, pixel *pixels)
{
	uint8_t padding8;
	uint16_t padding16;
	__uint24_t padding24;

	int i = 0;  // column
	int j = 0;  // row

	// writing individual pixels to file
	for (j=height-1; j>=0; j--)
	{
		for (i=0; i<width; i++)
		{
			fwrite(&pixels[j*width + i], 1, sizeof(pixel), file);
		}
		// include padding to fill the entire row
		if (width % 0x00000004 == 0x00000001)
		{
			fwrite(&padding8, 1, sizeof(padding8), file);
		}
		if (width % 0x00000004 == 0x00000002)
		{
			fwrite(&padding16, 1, sizeof(padding16), file);
		}
		if (width % 0x00000004 == 0x00000003)
		{
			fwrite(&padding24, 1, sizeof(padding24), file);
		}
	} 
    fclose(file);
}


void create_bmp(int width, int height, char *filepath, pixel *pixels)
{	
	FILE *image;
	
	image = fopen(filepath, "wb");
	if (image == NULL)
	{
		printf("Error opening file. Quitting.");
		exit(1);
	}
	write_header_to_file(width, height, image);
	fclose(image);
	
	image = fopen(filepath, "a");
    	if (image == NULL)
	{
		printf("Error opening file. Quitting.");
		exit(1);
	}
	dump_pixels_to_image(width, height, image, pixels);
    fclose(image);
}

