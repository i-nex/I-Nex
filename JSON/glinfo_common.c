/*
 * Copyright (C) 1999-2014  Brian Paul   All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glinfo_common.h"

#ifdef _WIN32
#define snprintf _snprintf
#endif


/**
 * Return the GL enum name for a numeric value.
 * We really only care about the compressed texture formats for now.
 */
static const char *
enum_name(GLenum val)
{
   static const struct {
      const char *name;
      GLenum val;
   } enums [] = {
      { "GL_COMPRESSED_ALPHA", 0x84E9 },
      { "GL_COMPRESSED_LUMINANCE", 0x84EA },
      { "GL_COMPRESSED_LUMINANCE_ALPHA", 0x84EB },
      { "GL_COMPRESSED_INTENSITY", 0x84EC },
      { "GL_COMPRESSED_RGB", 0x84ED },
      { "GL_COMPRESSED_RGBA", 0x84EE },
      { "GL_COMPRESSED_TEXTURE_FORMATS", 0x86A3 },
      { "GL_COMPRESSED_RGB", 0x84ED },
      { "GL_COMPRESSED_RGBA", 0x84EE },
      { "GL_COMPRESSED_TEXTURE_FORMATS", 0x86A3 },
      { "GL_COMPRESSED_ALPHA", 0x84E9 },
      { "GL_COMPRESSED_LUMINANCE", 0x84EA },
      { "GL_COMPRESSED_LUMINANCE_ALPHA", 0x84EB },
      { "GL_COMPRESSED_INTENSITY", 0x84EC },
      { "GL_COMPRESSED_SRGB", 0x8C48 },
      { "GL_COMPRESSED_SRGB_ALPHA", 0x8C49 },
      { "GL_COMPRESSED_SLUMINANCE", 0x8C4A },
      { "GL_COMPRESSED_SLUMINANCE_ALPHA", 0x8C4B },
      { "GL_COMPRESSED_RED", 0x8225 },
      { "GL_COMPRESSED_RG", 0x8226 },
      { "GL_COMPRESSED_RED_RGTC1", 0x8DBB },
      { "GL_COMPRESSED_SIGNED_RED_RGTC1", 0x8DBC },
      { "GL_COMPRESSED_RG_RGTC2", 0x8DBD },
      { "GL_COMPRESSED_SIGNED_RG_RGTC2", 0x8DBE },
      { "GL_COMPRESSED_RGB8_ETC2", 0x9274 },
      { "GL_COMPRESSED_SRGB8_ETC2", 0x9275 },
      { "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2", 0x9276 },
      { "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2", 0x9277 },
      { "GL_COMPRESSED_RGBA8_ETC2_EAC", 0x9278 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC", 0x9279 },
      { "GL_COMPRESSED_R11_EAC", 0x9270 },
      { "GL_COMPRESSED_SIGNED_R11_EAC", 0x9271 },
      { "GL_COMPRESSED_RG11_EAC", 0x9272 },
      { "GL_COMPRESSED_SIGNED_RG11_EAC", 0x9273 },
      { "GL_COMPRESSED_ALPHA_ARB", 0x84E9 },
      { "GL_COMPRESSED_LUMINANCE_ARB", 0x84EA },
      { "GL_COMPRESSED_LUMINANCE_ALPHA_ARB", 0x84EB },
      { "GL_COMPRESSED_INTENSITY_ARB", 0x84EC },
      { "GL_COMPRESSED_RGB_ARB", 0x84ED },
      { "GL_COMPRESSED_RGBA_ARB", 0x84EE },
      { "GL_COMPRESSED_TEXTURE_FORMATS_ARB", 0x86A3 },
      { "GL_COMPRESSED_RGBA_BPTC_UNORM_ARB", 0x8E8C },
      { "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB", 0x8E8D },
      { "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB", 0x8E8E },
      { "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB", 0x8E8F },
      { "GL_COMPRESSED_RGBA_ASTC_4x4_KHR", 0x93B0 },
      { "GL_COMPRESSED_RGBA_ASTC_5x4_KHR", 0x93B1 },
      { "GL_COMPRESSED_RGBA_ASTC_5x5_KHR", 0x93B2 },
      { "GL_COMPRESSED_RGBA_ASTC_6x5_KHR", 0x93B3 },
      { "GL_COMPRESSED_RGBA_ASTC_6x6_KHR", 0x93B4 },
      { "GL_COMPRESSED_RGBA_ASTC_8x5_KHR", 0x93B5 },
      { "GL_COMPRESSED_RGBA_ASTC_8x6_KHR", 0x93B6 },
      { "GL_COMPRESSED_RGBA_ASTC_8x8_KHR", 0x93B7 },
      { "GL_COMPRESSED_RGBA_ASTC_10x5_KHR", 0x93B8 },
      { "GL_COMPRESSED_RGBA_ASTC_10x6_KHR", 0x93B9 },
      { "GL_COMPRESSED_RGBA_ASTC_10x8_KHR", 0x93BA },
      { "GL_COMPRESSED_RGBA_ASTC_10x10_KHR", 0x93BB },
      { "GL_COMPRESSED_RGBA_ASTC_12x10_KHR", 0x93BC },
      { "GL_COMPRESSED_RGBA_ASTC_12x12_KHR", 0x93BD },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR", 0x93D0 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR", 0x93D1 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR", 0x93D2 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR", 0x93D3 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR", 0x93D4 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR", 0x93D5 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR", 0x93D6 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR", 0x93D7 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR", 0x93D8 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR", 0x93D9 },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR", 0x93DA },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR", 0x93DB },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR", 0x93DC },
      { "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR", 0x93DD },
      { "GL_COMPRESSED_RGB_FXT1_3DFX", 0x86B0 },
      { "GL_COMPRESSED_RGBA_FXT1_3DFX", 0x86B1 },
      { "GL_COMPRESSED_LUMINANCE_LATC1_EXT", 0x8C70 },
      { "GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT", 0x8C71 },
      { "GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT", 0x8C72 },
      { "GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT", 0x8C73 },
      { "GL_COMPRESSED_RED_RGTC1_EXT", 0x8DBB },
      { "GL_COMPRESSED_SIGNED_RED_RGTC1_EXT", 0x8DBC },
      { "GL_COMPRESSED_RED_GREEN_RGTC2_EXT", 0x8DBD },
      { "GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT", 0x8DBE },
      { "GL_COMPRESSED_RGB_S3TC_DXT1_EXT", 0x83F0 },
      { "GL_COMPRESSED_RGBA_S3TC_DXT1_EXT", 0x83F1 },
      { "GL_COMPRESSED_RGBA_S3TC_DXT3_EXT", 0x83F2 },
      { "GL_COMPRESSED_RGBA_S3TC_DXT5_EXT", 0x83F3 },
      { "GL_COMPRESSED_SRGB_EXT", 0x8C48 },
      { "GL_COMPRESSED_SRGB_ALPHA_EXT", 0x8C49 },
      { "GL_COMPRESSED_SLUMINANCE_EXT", 0x8C4A },
      { "GL_COMPRESSED_SLUMINANCE_ALPHA_EXT", 0x8C4B },
      { "GL_COMPRESSED_SRGB_S3TC_DXT1_EXT", 0x8C4C },
      { "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT", 0x8C4D },
      { "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT", 0x8C4E },
      { "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT", 0x8C4F },
      { "GL_PALETTE4_RGB8_OES", 0x8B90 },
      { "GL_PALETTE4_RGBA8_OES", 0x8B91 },
      { "GL_PALETTE4_R5_G6_B5_OES", 0x8B92 },
      { "GL_PALETTE4_RGBA4_OES", 0x8B93 },
      { "GL_PALETTE4_RGB5_A1_OES", 0x8B94 },
      { "GL_PALETTE8_RGB8_OES", 0x8B95 },
      { "GL_PALETTE8_RGBA8_OES", 0x8B96 },
      { "GL_PALETTE8_R5_G6_B5_OES", 0x8B97 },
      { "GL_PALETTE8_RGBA4_OES", 0x8B98 },
      { "GL_PALETTE8_RGB5_A1_OES", 0x8B99 }
   };
   const int n = sizeof(enums) / sizeof(enums[0]);
   static char buffer[100];
   int i;
   for (i = 0; i < n; i++) {
      if (enums[i].val == val) {
         return enums[i].name;
      }
   }
   /* enum val not found, just print hexadecimal value into static buffer */
   snprintf(buffer, sizeof(buffer), "0x%x", val);
   return buffer;
}


/*
 * qsort callback for string comparison.
 */
static int
compare_string_ptr(const void *p1, const void *p2)
{
   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

/*
 * Print a list of extensions, with word-wrapping.
 */
void
print_extension_list(const char *ext, GLboolean singleLine)
{
   char **extensions;
   int num_extensions;
   const char *indentString = "    ";
   const int indent = 4;
   const int max = 79;
   int width, i, j, k;

   if (!ext || !ext[0])
      return;

   /* count the number of extensions, ignoring successive spaces */
   num_extensions = 0;
   j = 1;
   do {
      if ((ext[j] == ' ' || ext[j] == 0) && ext[j - 1] != ' ') {
         ++num_extensions;
      }
   } while(ext[j++]);

   /* copy individual extensions to an array */
   extensions = malloc(num_extensions * sizeof *extensions);
   if (!extensions) {
      fprintf(stderr, "Error: malloc() failed\n");
      exit(1);
   }
   i = j = k = 0;
   while (1) {
      if (ext[j] == ' ' || ext[j] == 0) {
         /* found end of an extension name */
         const int len = j - i;

         if (len) {
            assert(k < num_extensions);

            extensions[k] = malloc(len + 1);
            if (!extensions[k]) {
               fprintf(stderr, "Error: malloc() failed\n");
               exit(1);
            }

            memcpy(extensions[k], ext + i, len);
            extensions[k][len] = 0;

            ++k;
         };

         i += len + 1;

         if (ext[j] == 0) {
            break;
         }
      }
      j++;
   }
   assert(k == num_extensions);

   /* sort extensions alphabetically */
   qsort(extensions, num_extensions, sizeof extensions[0], compare_string_ptr);

   /* print the extensions */
   width = indent;
   printf("%s", indentString);
   for (k = 0; k < num_extensions; ++k) {
      const int len = strlen(extensions[k]);
      if ((!singleLine) && (width + len > max)) {
         /* start a new line */
         printf("\n");
         width = indent;
         printf("%s", indentString);
      }
      /* print the extension name */
      printf("%s", extensions[k]);

      /* either we're all done, or we'll continue with next extension */
      width += len + 1;

      if (singleLine) {
         printf("\n");
         width = indent;
         printf("%s", indentString);
      }
      else if (k < (num_extensions -1)) {
         printf(", ");
         width += 2;
      }
   }
   printf("\n");

   for (k = 0; k < num_extensions; ++k) {
      free(extensions[k]);
   }
   free(extensions);
}




/**
 * Get list of OpenGL extensions using core profile's glGetStringi().
 */
char *
build_core_profile_extension_list(const struct ext_functions *extfuncs)
{
   GLint i, n, totalLen;
   char *buffer;

   glGetIntegerv(GL_NUM_EXTENSIONS, &n);

   /* compute totalLen */
   totalLen = 0;
   for (i = 0; i < n; i++) {
      const char *ext = (const char *) extfuncs->GetStringi(GL_EXTENSIONS, i);
      totalLen += strlen(ext) + 1; /* plus a space */
   }

   buffer = malloc(totalLen + 1);
   if (buffer) {
      int pos = 0;
      for (i = 0; i < n; i++) {
         const char *ext = (const char *) extfuncs->GetStringi(GL_EXTENSIONS, i);
         strcpy(buffer + pos, ext);
         pos += strlen(ext);
         buffer[pos++] = ' ';
      }
      buffer[pos] = '\0';
   }
   return buffer;
}


/** Is extension 'ext' supported? */
GLboolean
extension_supported(const char *ext, const char *extensionsList)
{
   while (1) {
      const char *p = strstr(extensionsList, ext);
      if (p) {
         /* check that next char is a space or end of string */
         int extLen = strlen(ext);
         if (p[extLen] == 0 || p[extLen] == ' ') {
            return 1;
         }
         else {
            /* We found a superset string, keep looking */
            extensionsList += extLen;
         }
      }
      else {
         break;
      }
   }
   return 0;
}


struct token_name
{
   GLenum token;
   const char *name;
};


static void
print_shader_limit_list(const struct token_name *lim)
{
   GLint max[1];
   unsigned i;

   for (i = 0; lim[i].token; i++) {
      glGetIntegerv(lim[i].token, max);
      if (glGetError() == GL_NO_ERROR) {
	 printf("        %s = %d\n", lim[i].name, max[0]);
      }
   }
}


/**
 * Print interesting limits for vertex/fragment shaders.
 */
static void
print_shader_limits(GLenum target)
{
   static const struct token_name vertex_limits[] = {
      { GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB, "GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB" },
      { GL_MAX_VARYING_FLOATS_ARB, "GL_MAX_VARYING_FLOATS_ARB" },
      { GL_MAX_VERTEX_ATTRIBS_ARB, "GL_MAX_VERTEX_ATTRIBS_ARB" },
      { GL_MAX_TEXTURE_IMAGE_UNITS_ARB, "GL_MAX_TEXTURE_IMAGE_UNITS_ARB" },
      { GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB" },
      { GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB, "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB" },
      { GL_MAX_TEXTURE_COORDS_ARB, "GL_MAX_TEXTURE_COORDS_ARB" },
      { GL_MAX_VERTEX_OUTPUT_COMPONENTS  , "GL_MAX_VERTEX_OUTPUT_COMPONENTS  " },
      { (GLenum) 0, NULL }
   };
   static const struct token_name fragment_limits[] = {
      { GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB, "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB" },
      { GL_MAX_TEXTURE_COORDS_ARB, "GL_MAX_TEXTURE_COORDS_ARB" },
      { GL_MAX_TEXTURE_IMAGE_UNITS_ARB, "GL_MAX_TEXTURE_IMAGE_UNITS_ARB" },
      { GL_MAX_FRAGMENT_INPUT_COMPONENTS , "GL_MAX_FRAGMENT_INPUT_COMPONENTS " },
      { (GLenum) 0, NULL }
   };
   static const struct token_name geometry_limits[] = {
      { GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS" },
      { GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS" },
      { GL_MAX_GEOMETRY_OUTPUT_VERTICES  , "GL_MAX_GEOMETRY_OUTPUT_VERTICES  " },
      { GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, "GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS" },
      { GL_MAX_GEOMETRY_INPUT_COMPONENTS , "GL_MAX_GEOMETRY_INPUT_COMPONENTS " },
      { GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, "GL_MAX_GEOMETRY_OUTPUT_COMPONENTS" },
      { (GLenum) 0, NULL }
   };

   switch (target) {
   case GL_VERTEX_SHADER:
      printf("    GL_VERTEX_SHADER_ARB:\n");
      print_shader_limit_list(vertex_limits);
      break;

   case GL_FRAGMENT_SHADER:
      printf("    GL_FRAGMENT_SHADER_ARB:\n");
      print_shader_limit_list(fragment_limits);
      break;

   case GL_GEOMETRY_SHADER:
      printf("    GL_GEOMETRY_SHADER:\n");
      print_shader_limit_list(geometry_limits);
      break;
   }
}


/**
 * Print interesting limits for vertex/fragment programs.
 */
static void
print_program_limits(GLenum target, 
                     const struct ext_functions *extfuncs)
{
#if defined(GL_ARB_vertex_program) || defined(GL_ARB_fragment_program)
   struct token_name {
      GLenum token;
      const char *name;
   };
   static const struct token_name common_limits[] = {
      { GL_MAX_PROGRAM_INSTRUCTIONS_ARB, "GL_MAX_PROGRAM_INSTRUCTIONS_ARB" },
      { GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB, "GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB" },
      { GL_MAX_PROGRAM_TEMPORARIES_ARB, "GL_MAX_PROGRAM_TEMPORARIES_ARB" },
      { GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB, "GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB" },
      { GL_MAX_PROGRAM_PARAMETERS_ARB, "GL_MAX_PROGRAM_PARAMETERS_ARB" },
      { GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB, "GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB" },
      { GL_MAX_PROGRAM_ATTRIBS_ARB, "GL_MAX_PROGRAM_ATTRIBS_ARB" },
      { GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB, "GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB" },
      { GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB, "GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB" },
      { GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB, "GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB" },
      { GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB, "GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB" },
      { GL_MAX_PROGRAM_ENV_PARAMETERS_ARB, "GL_MAX_PROGRAM_ENV_PARAMETERS_ARB" },
      { (GLenum) 0, NULL }
   };
   static const struct token_name fragment_limits[] = {
      { GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB, "GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB" },
      { GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB, "GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB" },
      { GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB, "GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB" },
      { GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB, "GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB" },
      { GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB, "GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB" },
      { GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB, "GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB" },
      { (GLenum) 0, NULL }
   };

   GLint max[1];
   int i;

   if (target == GL_VERTEX_PROGRAM_ARB) {
      printf("    GL_VERTEX_PROGRAM_ARB:\n");
   }
   else if (target == GL_FRAGMENT_PROGRAM_ARB) {
      printf("    GL_FRAGMENT_PROGRAM_ARB:\n");
   }
   else {
      return; /* something's wrong */
   }

   for (i = 0; common_limits[i].token; i++) {
      extfuncs->GetProgramivARB(target, common_limits[i].token, max);
      if (glGetError() == GL_NO_ERROR) {
         printf("        %s = %d\n", common_limits[i].name, max[0]);
      }
   }
   if (target == GL_FRAGMENT_PROGRAM_ARB) {
      for (i = 0; fragment_limits[i].token; i++) {
         extfuncs->GetProgramivARB(target, fragment_limits[i].token, max);
         if (glGetError() == GL_NO_ERROR) {
            printf("        %s = %d\n", fragment_limits[i].name, max[0]);
         }
      }
   }
#endif /* GL_ARB_vertex_program / GL_ARB_fragment_program */
}


/**
 * Print interesting OpenGL implementation limits.
 * \param version  20, 21, 30, 31, 32, etc.
 */
void
print_limits(const char *extensions, const char *oglstring, int version,
             const struct ext_functions *extfuncs)
{
   struct token_name {
      GLuint count;
      GLenum token;
      const char *name;
      const char *extension;
   };
   static const struct token_name limits[] = {
      { 1, GL_MAX_ATTRIB_STACK_DEPTH, "GL_MAX_ATTRIB_STACK_DEPTH", NULL },
      { 1, GL_MAX_CLIENT_ATTRIB_STACK_DEPTH, "GL_MAX_CLIENT_ATTRIB_STACK_DEPTH", NULL },
      { 1, GL_MAX_CLIP_PLANES, "GL_MAX_CLIP_PLANES", NULL },
      { 1, GL_MAX_COLOR_MATRIX_STACK_DEPTH, "GL_MAX_COLOR_MATRIX_STACK_DEPTH", "GL_ARB_imaging" },
      { 1, GL_MAX_ELEMENTS_VERTICES, "GL_MAX_ELEMENTS_VERTICES", NULL },
      { 1, GL_MAX_ELEMENTS_INDICES, "GL_MAX_ELEMENTS_INDICES", NULL },
      { 1, GL_MAX_EVAL_ORDER, "GL_MAX_EVAL_ORDER", NULL },
      { 1, GL_MAX_LIGHTS, "GL_MAX_LIGHTS", NULL },
      { 1, GL_MAX_LIST_NESTING, "GL_MAX_LIST_NESTING", NULL },
      { 1, GL_MAX_MODELVIEW_STACK_DEPTH, "GL_MAX_MODELVIEW_STACK_DEPTH", NULL },
      { 1, GL_MAX_NAME_STACK_DEPTH, "GL_MAX_NAME_STACK_DEPTH", NULL },
      { 1, GL_MAX_PIXEL_MAP_TABLE, "GL_MAX_PIXEL_MAP_TABLE", NULL },
      { 1, GL_MAX_PROJECTION_STACK_DEPTH, "GL_MAX_PROJECTION_STACK_DEPTH", NULL },
      { 1, GL_MAX_TEXTURE_STACK_DEPTH, "GL_MAX_TEXTURE_STACK_DEPTH", NULL },
      { 1, GL_MAX_TEXTURE_SIZE, "GL_MAX_TEXTURE_SIZE", NULL },
      { 1, GL_MAX_3D_TEXTURE_SIZE, "GL_MAX_3D_TEXTURE_SIZE", NULL },
      { 2, GL_MAX_VIEWPORT_DIMS, "GL_MAX_VIEWPORT_DIMS", NULL },
      { 2, GL_ALIASED_LINE_WIDTH_RANGE, "GL_ALIASED_LINE_WIDTH_RANGE", NULL },
      { 2, GL_SMOOTH_LINE_WIDTH_RANGE, "GL_SMOOTH_LINE_WIDTH_RANGE", NULL },
      { 2, GL_ALIASED_POINT_SIZE_RANGE, "GL_ALIASED_POINT_SIZE_RANGE", NULL },
      { 2, GL_SMOOTH_POINT_SIZE_RANGE, "GL_SMOOTH_POINT_SIZE_RANGE", NULL },
#if defined(GL_ARB_texture_cube_map)
      { 1, GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB, "GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB", "GL_ARB_texture_cube_map" },
#endif
#if defined(GL_NV_texture_rectangle)
      { 1, GL_MAX_RECTANGLE_TEXTURE_SIZE_NV, "GL_MAX_RECTANGLE_TEXTURE_SIZE_NV", "GL_NV_texture_rectangle" },
#endif
#if defined(GL_ARB_multitexture)
      { 1, GL_MAX_TEXTURE_UNITS_ARB, "GL_MAX_TEXTURE_UNITS_ARB", "GL_ARB_multitexture" },
#endif
#if defined(GL_EXT_texture_lod_bias)
      { 1, GL_MAX_TEXTURE_LOD_BIAS_EXT, "GL_MAX_TEXTURE_LOD_BIAS_EXT", "GL_EXT_texture_lod_bias" },
#endif
#if defined(GL_EXT_texture_filter_anisotropic)
      { 1, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT", "GL_EXT_texture_filter_anisotropic" },
#endif
#if defined(GL_ARB_draw_buffers)
      { 1, GL_MAX_DRAW_BUFFERS_ARB, "GL_MAX_DRAW_BUFFERS_ARB", "GL_ARB_draw_buffers" },
#endif
#if defined(GL_ARB_blend_func_extended)
      { 1, GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, "GL_MAX_DUAL_SOURCE_DRAW_BUFFERS", "GL_ARB_blend_func_extended" },
#endif
#if defined (GL_ARB_framebuffer_object)
      { 1, GL_MAX_RENDERBUFFER_SIZE, "GL_MAX_RENDERBUFFER_SIZE", "GL_ARB_framebuffer_object" },
      { 1, GL_MAX_COLOR_ATTACHMENTS, "GL_MAX_COLOR_ATTACHMENTS", "GL_ARB_framebuffer_object" },
      { 1, GL_MAX_SAMPLES, "GL_MAX_SAMPLES", "GL_ARB_framebuffer_object" },
#endif
      { 0, (GLenum) 0, NULL, NULL }
   };
   GLint i, max[2];

   printf("%s limits:\n", oglstring);
   for (i = 0; limits[i].count; i++) {
      if (!limits[i].extension ||
          extension_supported(limits[i].extension, extensions)) {
         glGetIntegerv(limits[i].token, max);
         if (glGetError() == GL_NO_ERROR) {
            if (limits[i].count == 1)
               printf("    %s = %d\n", limits[i].name, max[0]);
            else /* XXX fix if we ever query something with more than 2 values */
               printf("    %s = %d, %d\n", limits[i].name, max[0], max[1]);
         }
      }
   }

   /* these don't fit into the above mechanism, unfortunately */
   if (extension_supported("GL_ARB_imaging", extensions)) {
      extfuncs->GetConvolutionParameteriv(GL_CONVOLUTION_2D,
                                          GL_MAX_CONVOLUTION_WIDTH, max);
      extfuncs->GetConvolutionParameteriv(GL_CONVOLUTION_2D,
                                          GL_MAX_CONVOLUTION_HEIGHT, max+1);
      printf("    GL_MAX_CONVOLUTION_WIDTH/HEIGHT = %d, %d\n", max[0], max[1]);
   }

   if (extension_supported("GL_ARB_texture_compression", extensions)) {
      GLint i, n;
      GLint *formats;
      glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &n);
      printf("    GL_NUM_COMPRESSED_TEXTURE_FORMATS = %d\n", n);
      formats = (GLint *) malloc(n * sizeof(GLint));
      glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, formats);
      for (i = 0; i < n; i++) {
         printf("        %s\n", enum_name(formats[i]));
      }
      free(formats);
   }
#if defined(GL_ARB_vertex_program)
   if (extension_supported("GL_ARB_vertex_program", extensions)) {
      print_program_limits(GL_VERTEX_PROGRAM_ARB, extfuncs);
   }
#endif
#if defined(GL_ARB_fragment_program)
   if (extension_supported("GL_ARB_fragment_program", extensions)) {
      print_program_limits(GL_FRAGMENT_PROGRAM_ARB, extfuncs);
   }
#endif
   if (extension_supported("GL_ARB_vertex_shader", extensions)) {
      print_shader_limits(GL_VERTEX_SHADER_ARB);
   }
   if (extension_supported("GL_ARB_fragment_shader", extensions)) {
      print_shader_limits(GL_FRAGMENT_SHADER_ARB);
   }
   if (version >= 32) {
      print_shader_limits(GL_GEOMETRY_SHADER);
   }
}



/**
 * Return string representation for bits in a bitmask.
 */
const char *
bitmask_to_string(const struct bit_info bits[], int numBits, int mask)
{
   static char buffer[256], *p;
   int i;

   strcpy(buffer, "(none)");
   p = buffer;
   for (i = 0; i < numBits; i++) {
      if (mask & bits[i].bit) {
         if (p > buffer)
            *p++ = ',';
         strcpy(p, bits[i].name);
         p += strlen(bits[i].name);
      }
   }

   return buffer;
}

/**
 * Return string representation for the bitmask returned by
 * GL_CONTEXT_PROFILE_MASK (OpenGL 3.2 or later).
 */
const char *
profile_mask_string(int mask)
{
   const static struct bit_info bits[] = {
#ifdef GL_CONTEXT_CORE_PROFILE_BIT
      { GL_CONTEXT_CORE_PROFILE_BIT, "core profile"},
#endif
#ifdef GL_CONTEXT_COMPATIBILITY_PROFILE_BIT
      { GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, "compatibility profile" }
#endif
   };

   return bitmask_to_string(bits, ELEMENTS(bits), mask);
}


/**
 * Return string representation for the bitmask returned by
 * GL_CONTEXT_FLAGS (OpenGL 3.0 or later).
 */
const char *
context_flags_string(int mask)
{
   const static struct bit_info bits[] = {
#ifdef GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT
      { GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT, "forward-compatible" },
#endif
#ifdef GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB
      { GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB, "robust-access" },
#endif
   };

   return bitmask_to_string(bits, ELEMENTS(bits), mask);
}


