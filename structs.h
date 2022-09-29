typedef struct __attribute__((packed))  // BITMAP header
{
	
		uint16_t signature; //signature, must be 4d42
		uint32_t size; //file size bytes
		uint16_t reserved1; //must be 0000
		uint16_t reserved2; //must be 0000
		uint32_t offset; //offset to start of image data in bytes (54 bytes)
		uint32_t dib_header_size; //contains information about the dimensions and color format of a device independent bitmap (DIB)
		uint32_t width; //width in pixels
		uint32_t height; //height in pixels
		uint16_t planes; //number of planes in the image, must be set to 1 (#HRV plane = ravniva, mi radimo s fotkom, dakle 2D = 1 ravnina)
		uint16_t bits_px; //number of bits per pixel (1,4,8 or 24)
		uint32_t compression; //compression type (0 = none, 1 = RLE-8, 2 = RLE-4)
		uint32_t image_data_size; //size of image data in bytes (including padding)
		uint32_t horizontal_resolution_ppm; //horizontal resolution in pixels per meter (ppm)
		uint32_t vertical_resolution_ppm; //vertical resolution in pixels per meter (ppm)
		uint32_t colors; //number of colors in image
		uint32_t important_colors; //number of important colors in image
} BMPHeader;
	
	
typedef struct __attribute__((packed))  // RGB pixel, 8bits per color
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
} pixel;

typedef struct __attribute__((packed))  // uint24_t
{
	uint32_t value : 24;
} __uint24_t;