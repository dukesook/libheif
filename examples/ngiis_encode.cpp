#include <iostream>
#include <libheif/heif_cxx.h>

#include <string>
using namespace std;


//Heif Error - Check to see if a function was successful
void he (struct heif_error error) {
  if (error.code) {
    printf("ERROR! - %s\n", error.message);
    exit(error.code);
  }
}

//PRIMARY FUNCTIONS
static void get_pixel_data(const char* filename) {
  //Create New Context
  heif_context* ctx = heif_context_alloc();
  
  //Read HEIF from file
  he (heif_context_read_from_file(ctx, filename, nullptr) );

  //Get Primary Image Handle
  heif_image_handle* handle; //The heif_image_handle acts as a wrapper around the heif_image
  he (heif_context_get_primary_image_handle(ctx, &handle) );

  //Decode Image
  heif_image* img; //The pixel data is compressed when stored in a file.
  heif_colorspace colorspace = heif_colorspace_RGB; //Assuming the image is RGB
  heif_chroma chroma = heif_chroma_interleaved_RGB; //Assuming the image is Interleaved
  he (heif_decode_image(handle, &img, colorspace, chroma, nullptr) ); 

  //Get Pixel Data
  heif_channel channel = heif_channel_interleaved; //Assuming the image is Interleaved
  int stride; //Number of bytes in a row (not pixels)
  uint8_t* pixel_data = heif_image_get_plane(img, channel, &stride);

  //Print the first 5 pixels
  uint8_t r, g, b;
  int channel_count = 3;
  for (int i = 0; i < channel_count * 5; i = i + channel_count) {
    r = pixel_data[i + 0];  //Red
    g = pixel_data[i + 1];  //Green
    b = pixel_data[i + 2];  //Blue
    printf("r=%u g=%u b=%u\n", r, g, b);
  }

  //Get Width & Height
  int height = heif_image_get_height(img, channel);
  int width = heif_image_get_width(img, channel);
  printf("width: %d   height: %d\n", width, height);

}
static void heif_to_heif(string input_filename, string output_filename, heif_compression_format codec) {

  //GET CONTEXT
  heif_context* ctx = heif_context_alloc();
  he (heif_context_read_from_file(ctx, input_filename.c_str(), nullptr) );

  //GET HANDLE
  heif_image_handle* handle;
  he (heif_context_get_primary_image_handle(ctx, &handle) );

  //GET IMAGE
  heif_image* img;
  he (heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr) ); // decode the image and convert colorspace to RGB, saved as 24bit interleaved


  //GET ENCODER
  heif_context* ctx2 = heif_context_alloc(); //You need a separate context
  heif_encoder* encoder;
  he (heif_context_get_encoder_for_format(ctx2, codec, &encoder) );

  //ENCODE
  he (heif_context_encode_image(ctx2, img, encoder, nullptr, &handle) );

  //WRITE
  he (heif_context_write_to_file(ctx2, output_filename.c_str()) );
  printf("Created: %s\n", output_filename.c_str());

}

//MAIN
int main(int argc, char* argv[]) {
  cout << "***** ngiis_encode.cpp *****\n";
  printf("1=hevc  2=av1  3=j2k  4=unc\n");
  if (argc <= 2) {
    printf("ERROR - Specify input & output files\n");
    return 0;
  } 


  //VARIABLES
  char* input_filename = argv[1];
  char* output_filename = argv[2];
  int compression = 1; //default is HEVC

  if (argc == 4) {
    compression = atoi(argv[3]);
  }


  
  heif_compression_format codec = heif_compression_HEVC;
  switch(compression) {
    case 1:
      codec = heif_compression_HEVC;
    break;
    case 2:
      codec = heif_compression_AV1;
    break;
    case 3:
      codec = heif_compression_JPEG2000;
    break;
    case 4:
      codec = heif_compression_uncompressed;
    break;
    case 5:
      get_pixel_data(input_filename);
  }
  
  heif_to_heif(input_filename, output_filename, codec);

  cout << "***** End of ngiis_encode.cpp *****\n";
  return 0;
}

//***** README ******//
/*
  The examples_master branch:
    - should always be synced with libheif master.
    - provides examples for using the latest version of libheif.
      This could be done in another project, but is added here for
      convenience & running the debugger.
    - changes CMakeLists.txt to generate example executables & allow warnings
    - adds ngiis_xxxxxx.cpp source code
    - Tracks launch.json. I'm sick of re-writing this file.
    - makes no other changes to libheif to prevent git merge conflicts

  All personal branches should branch off of examples_master, not master.
  This ensures you that every branch has a framework for running examples.
  
  If you want to push back to libheif, you need two branches:
    1. One branch that's intended to be pushed. It's easy to just remove personal examples
    2. An identical branch with examples running your new code.

  Other programs shall not depend on this repository because it switches
  between branches so frequently. Other programs need to depend on a
  lit (locked in time) repository found in ~/lit/
*/