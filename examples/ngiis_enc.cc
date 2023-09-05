#include <iostream>
#include <libheif/heif_cxx.h>
#include <chrono> //timestamp
#include <string>
#include <cstring>
using namespace std;

#include "ngiis_ism_xml.h"
#include "libheif/api_structs.h" // I shouldn't have to include this, but ngiis_enc isn't seeing my new struct heif_infe_item




void he (struct heif_error error) {
  if (error.code) {
    printf("ERROR! - subcode: %d  Message: %s\n", error.subcode, error.message);
    exit(error.code);
  }
}

void heif_to_heif(string input_filename, string output_filename) {
  
  //GET CONTEXT
  heif_context* ctx = heif_context_alloc();
  he (heif_context_read_from_file(ctx, input_filename.c_str(), nullptr) );

  //GET HANDLE
  heif_image_handle* handle;
  he (heif_context_get_primary_image_handle(ctx, &handle) );

  //GET IMAGE
  heif_image* img;
  he (heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr) ); // decode the image and convert colorspace to RGB, saved as 24bit interleaved



  //ENCODE
  heif_encoder* encoder;
  heif_context* ctx2 = heif_context_alloc(); //You need a separate context
  he (heif_context_get_encoder_for_format(ctx2, heif_compression_HEVC, &encoder) );
  he (heif_context_encode_image(ctx2, img, encoder, nullptr, &handle) );

  //WRITE
  he (heif_context_write_to_file(ctx2, output_filename.c_str()) );
  printf("Created: %s\n", output_filename.c_str());

}
 
static uint64_t get_time() {
  auto now = std::chrono::system_clock::now();
  uint64_t time = now.time_since_epoch().count();
  return time;
}

static void heif_to_j2k(string input_filename, string output_filename) {
  //GET CONTEXT
  heif_context* ctx = heif_context_alloc();
  he (heif_context_read_from_file(ctx, input_filename.c_str(), nullptr) );

  //GET HANDLE
  heif_image_handle* handle;
  he (heif_context_get_primary_image_handle(ctx, &handle) );

  //GET IMAGE
  heif_image* img;
  he (heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr) ); // decode the image and convert colorspace to RGB, saved as 24bit interleaved




  //REGISTER ENCODER
  // const heif_encoder_plugin* plugin = get_encoder_plugin_openjpeg();
  // heif_register_encoder_plugin(plugin);


  //ENCODE
  heif_encoder* encoder;
  heif_context* ctx2 = heif_context_alloc(); //You need a separate context
  he (heif_context_get_encoder_for_format(ctx2, heif_compression_JPEG2000, &encoder) );
  he (heif_context_encode_image(ctx2, img, encoder, nullptr, &handle) );

  //WRITE
  he (heif_context_write_to_file(ctx2, output_filename.c_str()) );
  printf("Created: %s\n", output_filename.c_str());
}

static void heif_to_uncompressed(string input_filename, string output_filename) {
  //GET CONTEXT
  heif_context* ctx = heif_context_alloc();
  he (heif_context_read_from_file(ctx, input_filename.c_str(), nullptr) );

  //GET HANDLE
  heif_image_handle* handle;
  he (heif_context_get_primary_image_handle(ctx, &handle) );

  //GET IMAGE
  heif_image* img;
  he (heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr) ); // decode the image and convert colorspace to RGB, saved as 24bit interleaved



  //ENCODE
  heif_encoder* encoder;
  heif_context* ctx2 = heif_context_alloc(); //You need a separate context
  he (heif_context_get_encoder_for_format(ctx2, heif_compression_uncompressed, &encoder) );
  he (heif_context_encode_image(ctx2, img, encoder, nullptr, &handle) );

  //WRITE
  he (heif_context_write_to_file(ctx2, output_filename.c_str()) );
  printf("Created: %s\n", output_filename.c_str());
}

static void insert_odni_ism_xml(heif_context* ctx) {

  heif_infe_item x;
  x.data = ism_xml;
  x.size = (int) strlen(ism_xml);
  x.item_type = "mime";
  x.content_type = "application/dni-arh+xml";
  x.item_name = "ODNI ISM XML Security Marking";
  x.construction_method = 1;
  x.compression = heif_metadata_compression_off;
  x.associated_item_id = 0;

  heif_context_add_infe_metadata(ctx, &x);
}
static void insert_content_id(heif_context* ctx, heif_item_id id, const char* name) {

  //randomly generated
  // TODO - Use a library to generate uris
  const char *content_ids[] = {
    "urn:uuid:60ae321c-1bd5-5019-8727-addf87739b39", 
    "urn:uuid:8e249873-8666-5d13-b531-5946c045a8bc", 
  };

  static int call = 0;
  const char* data = content_ids[call++];


  heif_infe_item x;
  x.data = data;
  x.size = (int) strlen(data);
  x.item_type = "uri ";
  x.content_type = "Foo Bar";
  x.item_name = name;
  x.construction_method = 1;
  x.compression = heif_metadata_compression_off;
  x.associated_item_id = id;
  x.item_uri_type = "aac8ab7df5195437b7d3c973d1553253";

  heif_context_add_infe_metadata(ctx, &x);
}
static void insert_timestamp(heif_context* ctx, heif_item_id id) 
{

  //TODO - use mimd library

  uint8_t timestamp_bytes[8];
  uint64_t timestamp = get_time();
  printf("Timestamp: %ld = 0x%lx\n", timestamp, timestamp);
  // Convert the uint64_t to a uint_t[8]
  for (int i = 0; i < 8; i++) {
    timestamp_bytes[7-i] = (uint8_t)(timestamp >> (i * 8)) & 0xff;
  }


  heif_infe_item x;
  x.data = timestamp_bytes;
  x.size = sizeof(uint64_t);
  x.item_type = "uri ";
  x.content_type = "Foo Bar";
  x.item_name = "Timestamp";
  x.construction_method = 0;
  x.compression = heif_metadata_compression_off;
  x.associated_item_id = id;
  x.item_uri_type = "060E2B34020501010E01030209000000";

  heif_context_add_infe_metadata(ctx, &x);
}
static void gimme_gimi(string input_filename, string output_filename) {
  //GET CONTEXT
  heif_context* ctx = heif_context_alloc();
  he (heif_context_read_from_file(ctx, input_filename.c_str(), nullptr) );

  //GET HANDLE
  heif_image_handle* handle;
  he (heif_context_get_primary_image_handle(ctx, &handle) );

  //GET IMAGE
  heif_image* img;
  he (heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr) ); // decode the image and convert colorspace to RGB, saved as 24bit interleaved




  heif_encoder* encoder;
  heif_context* ctx2 = heif_context_alloc(); //You need a separate context

  // ITEM #1 - odni ism xml
  insert_odni_ism_xml(ctx2);

  // ITEM #2 - Content Id - odni ism
  insert_content_id(ctx2, 1, "Content ID for ODNI ISM");


  // ITEM #3 - unci
  he (heif_context_get_encoder_for_format(ctx2, heif_compression_uncompressed, &encoder) );
  he (heif_context_encode_image(ctx2, img, encoder, nullptr, &handle) );

  // ITEM #4 - Timestamp
  insert_timestamp(ctx2, 3);

  // ITEM #5 - Content Id - unci
  insert_content_id(ctx2, 3, "Content ID for Uncompressed Image");



  //WRITE
  he (heif_context_write_to_file(ctx2, output_filename.c_str()) );
  printf("Created: %s\n", output_filename.c_str());
}


int main(int argc, char* argv[]) {
  cout << "***** use_libhef.cpp *****\n";

  if (argc < 3) {
    printf("ERROR! - argument count is: %d\n", argc);
    for (int i = 0; i < argc; i++) {
      printf("%d: %s\n", i, argv[i]);
    }
    exit(1);
  }

  char* exe_path = argv[0];
  char* input_filename = argv[1];
  char* output_filename = argv[2];

  // heif_to_heif(input_filename, output_filename);
  // heif_to_j2k(input_filename, output_filename);
  // heif_to_uncompressed(input_filename, output_filename);
  gimme_gimi(input_filename, output_filename);


  cout << "***** end of use_libhef.cpp *****\n";
  return 0;
}


