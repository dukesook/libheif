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

static const char kSuccess[] = "Success";

static const char* openjpeg_plugin_name()
{

}


static void openjpeg_init_plugin()
{
}


static void openjpeg_deinit_plugin()
{
}


static int openjpeg_does_support_format(enum heif_compression_format format)
{

}


struct heif_error openjpeg_new_decoder(void** dec)
{


  struct heif_error err = {heif_error_Ok, heif_suberror_Unspecified, kSuccess};
  return err;
}


void openjpeg_free_decoder(void* decoder_raw)
{

}


void openjpeg_set_strict_decoding(void* decoder_raw, int flag)
{

}


struct heif_error openjpeg_push_data(void* decoder_raw, const void* frame_data, size_t frame_size)
{

}


struct heif_error openjpeg_decode_image(void* decoder_raw, struct heif_image** out_img)
{
 
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
