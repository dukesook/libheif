/*
 * AVIF codec.
 * Copyright (c) 2019 struktur AG, Dirk Farin <farin@struktur.de>
 *
 * This file is part of libheif.
 *
 * libheif is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * libheif is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libheif.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "libheif/heif.h"
#include "libheif/heif_plugin.h"
#include "decoder_openjpeg.h"
#include <openjpeg.h>
#include <cstring>

#include <vector>

static const char kSuccess[] = "Success";
static const int OPENJPEG_PLUGIN_PRIORITY = 100;

struct openjpeg_decoder
{
  std::vector<uint8_t> encoded_data;
};

static const char* openjpeg_plugin_name()
{
  return "OpenJPEG JPEG2000 Decoder";
}


static void openjpeg_init_plugin()
{
}


static void openjpeg_deinit_plugin()
{
}


static int openjpeg_does_support_format(enum heif_compression_format format)
{
  if (format == heif_compression_JPEG2000) {
    return OPENJPEG_PLUGIN_PRIORITY;
  }
  else {
    return 0;
  }
}


struct heif_error openjpeg_new_decoder(void** dec)
{
  struct openjpeg_decoder* decoder = new openjpeg_decoder();

  *dec = decoder;

  struct heif_error err = {heif_error_Ok, heif_suberror_Unspecified, kSuccess};
  return err;
}


void openjpeg_free_decoder(void* decoder_raw)
{
  struct openjpeg_decoder* decoder = (openjpeg_decoder*) decoder_raw;

  if (!decoder) {
    return;
  }

  delete decoder;
}


void openjpeg_set_strict_decoding(void* decoder_raw, int flag)
{

}


struct heif_error openjpeg_push_data(void* decoder_raw, const void* frame_data, size_t frame_size)
{
  struct openjpeg_decoder* decoder = (struct openjpeg_decoder*) decoder_raw;
  const uint8_t* frame_data_src = (const uint8_t*) frame_data;

  // decoder->data.data = frame_data;
  for (size_t i = 0; i < frame_size; i++) {
    decoder->encoded_data.push_back(frame_data_src[i]);
  }

  struct heif_error err = {heif_error_Ok, heif_suberror_Unspecified, kSuccess};
  return err;
}


//**************************************************************************
typedef struct
{

	OPJ_UINT8* pData; //Our data.

	OPJ_SIZE_T dataSize; //How big is our data.

	OPJ_SIZE_T offset; //Where are we currently in our data.

}opj_memory_stream;

//This will read from our memory to the buffer.

static OPJ_SIZE_T opj_memory_stream_read(void * p_buffer, OPJ_SIZE_T p_nb_bytes, void * p_user_data)

{

	opj_memory_stream* l_memory_stream = (opj_memory_stream*)p_user_data;//Our data.

	OPJ_SIZE_T l_nb_bytes_read = p_nb_bytes;//Amount to move to buffer.

	//Check if the current offset is outside our data buffer.

	if (l_memory_stream->offset >= l_memory_stream->dataSize) return (OPJ_SIZE_T)-1;

	//Check if we are reading more than we have.

	if (p_nb_bytes > (l_memory_stream->dataSize - l_memory_stream->offset))

		l_nb_bytes_read = l_memory_stream->dataSize - l_memory_stream->offset;//Read all we have.

	//Copy the data to the internal buffer.

	memcpy(p_buffer, &(l_memory_stream->pData[l_memory_stream->offset]), l_nb_bytes_read);

	l_memory_stream->offset += l_nb_bytes_read;//Update the pointer to the new location.

	return l_nb_bytes_read;

}

//This will write from the buffer to our memory.

static OPJ_SIZE_T opj_memory_stream_write(void * p_buffer, OPJ_SIZE_T p_nb_bytes, void * p_user_data)

{

	opj_memory_stream* l_memory_stream = (opj_memory_stream*)p_user_data;//Our data.

	OPJ_SIZE_T l_nb_bytes_write = p_nb_bytes;//Amount to move to buffer.

	//Check if the current offset is outside our data buffer.

	if (l_memory_stream->offset >= l_memory_stream->dataSize) return (OPJ_SIZE_T)-1;

	//Check if we are write more than we have space for.

	if (p_nb_bytes > (l_memory_stream->dataSize - l_memory_stream->offset))

		l_nb_bytes_write = l_memory_stream->dataSize - l_memory_stream->offset;//Write the remaining space.

	//Copy the data from the internal buffer.

	memcpy(&(l_memory_stream->pData[l_memory_stream->offset]), p_buffer, l_nb_bytes_write);

	l_memory_stream->offset += l_nb_bytes_write;//Update the pointer to the new location.

	return l_nb_bytes_write;

}

//Moves the pointer forward, but never more than we have.

static OPJ_OFF_T opj_memory_stream_skip(OPJ_OFF_T p_nb_bytes, void * p_user_data)

{

	opj_memory_stream* l_memory_stream = (opj_memory_stream*)p_user_data;

	OPJ_SIZE_T l_nb_bytes;



	if (p_nb_bytes < 0) return -1;//No skipping backwards.

	l_nb_bytes = (OPJ_SIZE_T)p_nb_bytes;//Allowed because it is positive.

	// Do not allow jumping past the end.

	if (l_nb_bytes >l_memory_stream->dataSize - l_memory_stream->offset)

		l_nb_bytes = l_memory_stream->dataSize - l_memory_stream->offset;//Jump the max.

	//Make the jump.

	l_memory_stream->offset += l_nb_bytes;

	//Returm how far we jumped.

	return l_nb_bytes;

}

//Sets the pointer to anywhere in the memory.

static OPJ_BOOL opj_memory_stream_seek(OPJ_OFF_T p_nb_bytes, void * p_user_data)

{

	opj_memory_stream* l_memory_stream = (opj_memory_stream*)p_user_data;



	if (p_nb_bytes < 0) return OPJ_FALSE;//No before the buffer.

	if (p_nb_bytes >(OPJ_OFF_T)l_memory_stream->dataSize) return OPJ_FALSE;//No after the buffer.

	l_memory_stream->offset = (OPJ_SIZE_T)p_nb_bytes;//Move to new position.

	return OPJ_TRUE;

}

//The system needs a routine to do when finished, the name tells you what I want it to do.

static void opj_memory_stream_do_nothing(void * p_user_data)

{

	OPJ_ARG_NOT_USED(p_user_data);

}

//Create a stream to use memory as the input or output.

opj_stream_t* opj_stream_create_default_memory_stream(opj_memory_stream* p_memoryStream, OPJ_BOOL p_is_read_stream)

{

	opj_stream_t* stream;



	if (!(stream = opj_stream_default_create(p_is_read_stream))) return (NULL);

	//Set how to work with the frame buffer.

	if(p_is_read_stream)

		opj_stream_set_read_function(stream, opj_memory_stream_read);

	else

		opj_stream_set_write_function(stream, opj_memory_stream_write);

	opj_stream_set_seek_function(stream, opj_memory_stream_seek);

	opj_stream_set_skip_function(stream, opj_memory_stream_skip);

	opj_stream_set_user_data(stream, p_memoryStream, opj_memory_stream_do_nothing);

	opj_stream_set_user_data_length(stream, p_memoryStream->dataSize);

	return stream;

}
//**************************************************************************



struct heif_error openjpeg_decode_image(void* decoder_raw, struct heif_image** out_img)
{
  struct openjpeg_decoder* decoder = (struct openjpeg_decoder*) decoder_raw;
  std::vector<uint8_t>* encoded_data = &decoder->encoded_data;



  OPJ_BOOL success;
  opj_dparameters_t decompression_parameters;
  opj_codec_t* l_codec;
  
  //Initialize Decoder
  opj_set_default_decoder_parameters(&decompression_parameters); 
  l_codec = opj_create_decompress(OPJ_CODEC_J2K);
  success = opj_setup_decoder(l_codec, &decompression_parameters);
  if (!success) {
    struct heif_error err = {heif_error_Decoder_plugin_error, heif_suberror_Unspecified, "opj_setup_decoder()"};
    return err;
  }




  //Create Input Stream



  opj_memory_stream memoryStream;
    memoryStream.pData = encoded_data->data();
    memoryStream.dataSize = encoded_data->size();
    memoryStream.offset = 0;
  OPJ_BOOL is_read_stream = true;
  opj_stream_t *stream = opj_stream_create_default_memory_stream(&memoryStream, is_read_stream);


  // Read Codestream Header
  opj_image_t* image = NULL;
  success = opj_read_header(stream, l_codec, &image);
  if (!success) {
    struct heif_error err = {heif_error_Decoder_plugin_error, heif_suberror_Unspecified, "opj_read_header()"};
    return err;
  }
  else if (image->numcomps != 3) {
    //TODO - Handle other numbers of components
    struct heif_error err = {heif_error_Unsupported_feature, heif_suberror_Unsupported_data_version, "Number of components must be 3"};
    return err;
  }
  else if ((image->color_space != OPJ_CLRSPC_UNSPECIFIED) && (image->color_space != OPJ_CLRSPC_SRGB) ) {
    //TODO - Handle other colorpsaces
    struct heif_error err = {heif_error_Unsupported_feature, heif_suberror_Unsupported_data_version, "Colorspace must be SRGB"};
    return err;
  }
  int width = (image->x1 - image->x0);
  int height = (image->y1 - image->y0);
  int pixel_count = width * height;


    /* Get the decoded image */
  success = opj_decode(l_codec, stream, image);
  if (!success) {
    struct heif_error err = {heif_error_Decoder_plugin_error, heif_suberror_Unspecified, "opj_decode()"};
    return err;
  }


  success = opj_end_decompress(l_codec, stream);
  if (!success) {
    struct heif_error err = {heif_error_Decoder_plugin_error, heif_suberror_Unspecified, "opj_end_decompress()"};
    return err;
  }

  
  /* Close the byte stream */
  opj_stream_destroy(stream);


  
  opj_image_comp_t opj_r = image->comps[0];
  opj_image_comp_t opj_g = image->comps[1];
  opj_image_comp_t opj_b = image->comps[2];
  



  heif_colorspace colorspace = heif_colorspace_RGB;
  heif_chroma chroma = heif_chroma_444; //heif_chroma_interleaved_RGB;

  struct heif_error error = heif_image_create(width, height, colorspace, chroma, out_img);
  if (error.code) {
    return error;
  }

  int bit_depth = 8;
  error = heif_image_add_plane(*out_img, heif_channel_R, width, height, bit_depth);
  error = heif_image_add_plane(*out_img, heif_channel_G, width, height, bit_depth);
  error = heif_image_add_plane(*out_img, heif_channel_B, width, height, bit_depth);

  int stride = -1;
  uint8_t* r = heif_image_get_plane(*out_img, heif_channel_R, &stride);
  uint8_t* g = heif_image_get_plane(*out_img, heif_channel_G, &stride);
  uint8_t* b = heif_image_get_plane(*out_img, heif_channel_B, &stride);

  if (stride == width) {
    for (int i = 0; i < pixel_count; i++) {

        r[i] = (uint8_t) opj_r.data[i];
        g[i] = (uint8_t) opj_g.data[i];
        b[i] = (uint8_t) opj_b.data[i];
    }
  }
  else {
    printf("width %d != stride %d\n", width , stride);
    int i = 0, i_opj = 0;
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        i = (stride * y) + x;
        i_opj = (width * y) + x;
        r[i] = (uint8_t) opj_r.data[i_opj];
        g[i] = (uint8_t) opj_g.data[i_opj];
        b[i] = (uint8_t) opj_b.data[i_opj];

      }
    }
  }

  return heif_error_ok;
}



static const struct heif_decoder_plugin decoder_openjpeg
{
    3,
    openjpeg_plugin_name,
    openjpeg_init_plugin,
    openjpeg_deinit_plugin,
    openjpeg_does_support_format,
    openjpeg_new_decoder,
    openjpeg_free_decoder,
    openjpeg_push_data,
    openjpeg_decode_image,
    openjpeg_set_strict_decoding,
    "openjpeg"
};

const struct heif_decoder_plugin* get_decoder_plugin_openjpeg()
{
  return &decoder_openjpeg;
}


#if PLUGIN_OPENJPEG_DECODER
heif_plugin_info plugin_info {
  1,
  heif_plugin_type_decoder,
  &decoder_openjpeg
};
#endif