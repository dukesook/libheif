/*
 * HEIF codec.
 * Copyright (c) 2017 struktur AG, Dirk Farin <farin@struktur.de>
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

#ifndef HEIF_API_STRUCTS_H
#define HEIF_API_STRUCTS_H

#include "pixelimage.h"
#include "context.h"

#include <memory>

struct heif_image_handle
{
  std::shared_ptr<HeifContext::Image> image;

  // store reference to keep the context alive while we are using the handle (issue #147)
  std::shared_ptr<HeifContext> context;
};


struct heif_image
{
  std::shared_ptr<HeifPixelImage> image;
};


struct heif_context
{
  std::shared_ptr<HeifContext> context;
};


struct heif_encoder
{
  heif_encoder(const struct heif_encoder_plugin* plugin);

  ~heif_encoder();

  struct heif_error alloc();

  void release();


  const struct heif_encoder_plugin* plugin;
  void* encoder = nullptr;
};


struct heif_region_item
{
  std::shared_ptr<HeifContext> context;
  std::shared_ptr<RegionItem> region_item;
};


struct heif_region
{
  std::shared_ptr<HeifContext> context; // we need this to perform coordinate transformation
  //heif_item_id parent_region_item_id; // we need this to perform coordinate transformation
  std::shared_ptr<RegionItem> region_item;
  std::shared_ptr<RegionGeometry> region;
};


struct heif_infe_item 
{
  const void* data;
  int size;                 //side of data
  const char* item_type;    // mime, uri , etc
  const char* content_type; 
  const char* item_name;    // optional
  const char* item_uri_type; //if item_type = "uri "
  uint8_t construction_method; // 0 = mdat, 1 = idat
  heif_item_id associated_item_id;  //
  heif_metadata_compression compression;
};

#endif
