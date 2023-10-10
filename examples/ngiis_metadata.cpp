#include <iostream>
#include <libheif/heif_cxx.h>
#include <string>
#include <string.h>
using namespace std;


//handle error
void he (struct heif_error error) {
  if (error.code) {
    printf("ERROR! - %s\n", error.message);
    exit(error.code);
  }
}



//PRIMARY FUNCTIONS

static void insert_udes(string input_filename, string output_filename) {

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
  he (heif_context_get_encoder_for_format(ctx2, heif_compression_HEVC, &encoder) );

  //ADD METADATA
  struct heif_property_user_description udes = {
    1,
    "English",
    "Examples udes box",
    "Demonstrate how to use a user description box",
    "Insert tags here"
  };
  heif_property_id* out_propertyId;
  heif_item_add_property_user_description(ctx2, 1, &udes, out_propertyId);

  //ENCODE
  he (heif_context_encode_image(ctx2, img, encoder, nullptr, &handle) );

  //WRITE
  he (heif_context_write_to_file(ctx2, output_filename.c_str()) );
  printf("Created: %s\n", output_filename.c_str());

}

static void insert_region(string input_filename, string output_filename) {

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
  he (heif_context_get_encoder_for_format(ctx2, heif_compression_HEVC, &encoder) );



  //ENCODE
  he (heif_context_encode_image(ctx2, img, encoder, nullptr, &handle) );


  //*************************************************************************************************
  //ADD METADATA
  uint32_t reference_width = 10;
  uint32_t reference_height = 10;
  heif_region_item *region_item_1, *region_item_2, *region_item_3;
  he( heif_image_handle_add_region_item(handle, reference_width, reference_height, &region_item_1) );
  he( heif_image_handle_add_region_item(handle, reference_width, reference_height, &region_item_2) );
  he( heif_image_handle_add_region_item(handle, reference_width, reference_height, &region_item_3) );

  int32_t x=100, y=100;
  heif_region* region;

  //POINTS
  he( heif_region_item_add_region_point(region_item_1, 944, 783, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 866, 1008, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1338, 1104, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 321, 569, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 876, 688, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1229, 704, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1387, 1162, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1360, 1187, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1397, 1203, nullptr) );

  he( heif_region_item_add_region_point(region_item_1, 1280, 905, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1318, 907, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1473, 918, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1584, 953, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1570, 870, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1632, 780, nullptr) );
  // he( heif_region_item_add_region_point(region_item_1, , , nullptr) );
  
  //RECTANGELS
  uint32_t width = 80;
  uint32_t height = 60;
  he( heif_region_item_add_region_rectangle(region_item_2, 11, 690, width, height, nullptr) );
  he( heif_region_item_add_region_rectangle(region_item_2, 202, 740, width+25, height, nullptr) );
  he( heif_region_item_add_region_rectangle(region_item_2, 85, 990, width, height, nullptr) );
  he( heif_region_item_add_region_rectangle(region_item_2, 371, 1009, width+10, height, nullptr) );

  uint32_t radius_x = 125;
  uint32_t radius_y = 150;
  he( heif_region_item_add_region_ellipse(region_item_3, 1919, 763, radius_x, radius_y, &region) );
  he( heif_region_item_add_region_ellipse(region_item_3, 1878, 1055, 235, 225, &region) );

  #if 0
  // Tatooine
  // he( heif_region_item_add_region_point(region_item_1, x, y, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 677, 169, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 644, 217, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 702, 219, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1180, 127, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1287, 179, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1258, 269, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1288, 307, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1018, 575, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 976, 616, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 967, 797, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1074, 768, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1326, 666, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1376, 661, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1224, 736, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1351, 734, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1221, 800, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1110, 882, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1352, 840, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1126, 941, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1176, 609, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1311, 564, nullptr) );
  he( heif_region_item_add_region_point(region_item_1, 1342, 527, nullptr) );
  // he( heif_region_item_add_region_point(region_item_1, , , nullptr) );
  
  uint32_t width = 70;
  uint32_t height = 60;
  he( heif_region_item_add_region_rectangle(region_item_2, 486, 322, width, height, nullptr) );
  he( heif_region_item_add_region_rectangle(region_item_2, 890, 760, width, height, nullptr) );
  he( heif_region_item_add_region_rectangle(region_item_2, 1139, 736, width, height, nullptr) );
  he( heif_region_item_add_region_rectangle(region_item_2, 914, 96, width, height, nullptr) );

  uint32_t radius_x = 10;
  uint32_t radius_y = 4;
  he( heif_region_item_add_region_ellipse(region_item_3, x, y, radius_x, radius_y, &region) );
  #endif

  
  //*************************************************************************************************


  //WRITE
  he (heif_context_write_to_file(ctx2, output_filename.c_str()) );
  printf("Created: %s\n", output_filename.c_str());

}


static void dump_regions(string input_filename) {

  //GET CONTEXT
  heif_context* ctx = heif_context_alloc();
  he (heif_context_read_from_file(ctx, input_filename.c_str(), nullptr) );

  //GET HANDLE
  heif_image_handle* handle;
  he (heif_context_get_primary_image_handle(ctx, &handle) );

  //GET IMAGE
  heif_image* img;
  he (heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr) ); // decode the image and convert colorspace to RGB, saved as 24bit interleaved

  //*************************************************************************************************

  int region_item_count = heif_image_handle_get_number_of_region_items(handle);
  printf("region_item_count: %d\n", region_item_count);

  heif_item_id region_item_ids[region_item_count];
  int output_count = heif_image_handle_get_list_of_region_item_ids(handle, region_item_ids, region_item_count);
  printf("region output count: %d\n", output_count);
  for (int i = 0; i < region_item_count; i++) {
    heif_item_id id = region_item_ids[i];
    printf("%d. %d\n", i, id);
    struct heif_region_item* out;
    he( heif_context_get_region_item(ctx, id, &out) );

    uint32_t ref_width,  ref_height;
    heif_region_item_get_reference_size(out, &ref_width, &ref_height);
    printf("\tRefernce width x height: %d x %d\n", ref_width, ref_height);

    int number_of_regions = heif_region_item_get_number_of_regions(out);
    printf("\tNumber of regions: %d\n", number_of_regions);


    heif_region* out_regions;
    int num_regions = heif_region_item_get_list_of_regions(out, &out_regions, number_of_regions);
    printf("\tNumber of regions filled: %d\n", num_regions);
    // heif_region_get_type()

    heif_region_type type = heif_region_get_type(out_regions);
    printf("\ttype: %d\n", type);

    int32_t x, y;
    uint32_t width, height, radius_x, radius_y;
    switch (type) {
      case heif_region_type_point:
        he (heif_region_get_point(out_regions, &x, &y) );
        printf("Point x=%d  y=%d\n", x, y);
      break;
      case heif_region_type_rectangle:
        heif_region_get_rectangle(out_regions, &x, &y, &width, &height);
        printf("Rectangle x=%d  y=%d  width=%d  height=%d\n", x, y, width, height);
      break;
      case heif_region_type_ellipse:
        heif_region_get_ellipse(out_regions, &x, &y, &radius_x, &radius_y);
        printf("Ellipse x=%d  y=%d  r_x=%d  r_y=%d\n", x, y, radius_x, radius_y);
      break;
    }
  }


}


static void dump_item(heif_infe_item item) {
    cout << "id: " << item.id << endl;
    cout << "data_size: " << item.size << endl;
    if (item.size < 600) {
      cout << "data: " << item.data << endl;
    }
    cout << "item_type: " << item.item_type << endl;
    cout << "content_type: " << item.content_type << endl;
    cout << "item_name: " << item.item_name << endl;
    cout << "item_uri_type: " << item.item_uri_type << endl;
    cout << endl;

    if (!strcmp(item.item_type, "mime")) {
      printf("mime detected\n");
      const char* s = (const char*) item.data;
      printf("%s\n", s);
      char* d = (char*) item.data;
      for (int i = 0; i < item.size; i++) {
        printf("%c", d[i]);
      } printf("\n");
    } 
    else if (!strcmp(item.item_type, "uri ")) {
      printf("uri detected\n");
      const char* s = (const char*) item.data;
      printf("%s\n", s);
      char* d = (char*) item.data;
      for (int i = 0; i < item.size; i++) {
        printf("%x", d[i]);
      } printf("\n");
    }
    else {
      printf("unknown item type: %s\n", item.item_type);
    }
}

static void dump_items(string input_filename) {

  //GET CONTEXT
  heif_context* ctx = heif_context_alloc();
  he (heif_context_read_from_file(ctx, input_filename.c_str(), nullptr) );

  int count = heif_context_get_item_count(ctx);
  cout << "ITEM COUNT: " << count << endl << endl;
  struct heif_infe_item items [count];

  he (heif_context_get_items(ctx, items) );

  for (int i = 0; i < count; i++) {
    // dump_item(items[i]);
  }


}


//MAIN
int main(int argc, char* argv[]) {
  cout << "***** ngiis_encode.cpp *****\n";

  char* exe_path = argv[0];
  char* input_filename = argv[1];
  char* output_filename = argv[2];
  int option = atoi(argv[3]);
  

  switch(option) {
    case 1:
      insert_udes(input_filename, output_filename);
    break;
    case 2:
      insert_region(input_filename, output_filename);
    break;
    case 3:
      dump_regions(input_filename);
    break;
    case 4:
      dump_items(input_filename);
    break;
  }
  

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