if(UNIX OR MINGW)
  find_package(PkgConfig)
  pkg_check_modules(GDKPIXBUF2 gdk-pixbuf-2.0)

  if(GDKPIXBUF2_FOUND)
    execute_process(
      COMMAND ${PKG_CONFIG_EXECUTABLE} gdk-pixbuf-2.0 --variable gdk_pixbuf_moduledir
              --define-variable=prefix=${CMAKE_INSTALL_PREFIX} OUTPUT_VARIABLE GDKPIXBUF2_MODULE_DIR
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    add_library(pixbufloader-heif MODULE pixbufloader-heif.c)

    target_include_directories(pixbufloader-heif PRIVATE ${GDKPIXBUF2_INCLUDE_DIRS} ${libheif_BINARY_DIR} ${libheif_SOURCE_DIR}/libheif/api)

    target_link_directories(pixbufloader-heif PRIVATE ${GDKPIXBUF2_LIBRARY_DIRS})

    target_link_libraries(pixbufloader-heif PUBLIC ${GDKPIXBUF2_LIBRARIES} heif)

    install(TARGETS pixbufloader-heif DESTINATION ${GDKPIXBUF2_MODULE_DIR})
  endif()
endif()
