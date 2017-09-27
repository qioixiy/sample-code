#include <stdio.h>
#include <stdlib.h>
#include "esUtil.h"

typedef struct
{
   // Handle to a program object
   GLuint programObject;

   // Attribute locations
   GLint  positionLoc;
   GLint  texCoordLoc;

   GLint texture_width;

  // Sampler locations
   GLint baseMapLoc;

   // Texture handle
   GLuint baseMapTexId;

} UserData;

unsigned char yuv2_buffer[640*480*2];
unsigned char *
read_data_from_file (const char *path, long size)
{
    FILE *fp;

    if ((fp = fopen (path, "rb")) == NULL)
    {
        printf ("cant open the file %s", path);
        exit (0);
    }

    unsigned char *buffer = malloc (size);
    fread (buffer, size, 1, fp);
    fclose (fp);

    return buffer;
}

///
// Initialize the shader and program object
//
int Init ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
   GLbyte *vShaderStr = read_data_from_file("shader.vert", 4096);
   GLbyte *fShaderStr = read_data_from_file("yuv2.frag", 4096);

   // Load the shaders and get a linked program object
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   userData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );
   
   // Get the sampler location
   userData->baseMapLoc = glGetUniformLocation ( userData->programObject, "s_baseMap" );

   userData->texture_width =  glGetUniformLocation(userData->programObject, "texture_width");
   
   // set the textures
   glGenTextures ( 1, &userData->baseMapTexId );
   glBindTexture ( GL_TEXTURE_2D, userData->baseMapTexId );

   if ( userData->baseMapTexId == 0 )
      return FALSE;

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
   GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                           -1.0f, -1.0f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            1.0f, -1.0f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            1.0f,  1.0f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex position
   glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 5 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );

   glEnableVertexAttribArray ( userData->positionLoc );
   glEnableVertexAttribArray ( userData->texCoordLoc );

   // Bind the base map
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, userData->baseMapTexId );
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, esContext->width, esContext->height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, yuv2_buffer );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

   // Set the base map sampler to texture unit to 0
   glUniform1i ( userData->baseMapLoc, 0 );
   glUniform1f( userData->texture_width, 640.0);

   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

   eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

///
// Cleanup
//
void ShutDown ( ESContext *esContext )
{
   UserData *userData = esContext->userData;

   // Delete texture object
   glDeleteTextures ( 1, &userData->baseMapTexId );

   // Delete program object
   glDeleteProgram ( userData->programObject );
}

void* gles_show_yuv2_main (void *p )
{
   ESContext esContext;
   UserData  userData;

   esInitContext ( &esContext );
   esContext.userData = &userData;

   esCreateWindow ( &esContext, "yuv2", 640, 480, ES_WINDOW_RGB );
   
   if ( !Init ( &esContext ) )
      return 0;

   esRegisterDrawFunc ( &esContext, Draw );
   
   esMainLoop ( &esContext );

   ShutDown ( &esContext );

   return 0;
}
