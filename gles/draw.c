
#include <stdio.h>
#include <GLES2/gl2.h>

#include "draw.h"
#include "shader.h"
#include "texture.h"
#include "cairo/cairo.h"
#include "utils/Matrix.h"

void show_default(int width, int height)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_default();
    }
    // Use the program object
    glUseProgram(program_object);

    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f};
// Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void draw_vertexs(GLfloat *vVerticess, int len)
{
    int index = 0;

    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_default();
    }
    // Use the program object
    glUseProgram(program_object);

// Load the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVerticess);
 
    glDrawArrays(GL_TRIANGLES, 0, len);
}

void draw_rect(float r, float g, float b)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_drawrect();
    }
    // Use the program object
    glUseProgram(program_object);

    GLint colorLoc = glGetUniformLocation(program_object, "colorLoc");
    GLfloat rgba[4] = {r, g, b, 1.0f};
    glUniform4fv(colorLoc, 1, rgba);
    GLfloat vVertices[] = {-1.0f, 1.0f, 0.0f,
                           1.0f, 1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,
                           -1.0f, 1.0f, 0.0f};

// Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void show_yuyv(int width, int height)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_showyuyv();
    }
    // Use the program object
    glUseProgram(program_object);

    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_yuyv_loc = glGetUniformLocation(program_object, "s_texture_yuyv");
    GLint texture_width = glGetUniformLocation(program_object, "texture_width");

    // Load the textures
    static GLuint texture_id_yuyv = 0;
    if (0 == texture_id_yuyv) {
        texture_id_yuyv =
            gen_texture_from_file("res/640x480.yuv2.yuv", width, height,
                                  GL_LUMINANCE_ALPHA);
    }
    
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
      
    // Load the vertex position
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);
    // Bind the base texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_yuyv);
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_yuyv_loc, 0);
    glUniform1f(texture_width, (GLfloat)width);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void show_nv12(int width, int height)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_shownv12();
    }
    // Use the program object
    glUseProgram(program_object);

    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_y_loc =
        glGetUniformLocation(program_object, "s_texture_y");
    GLint texture_uv_loc
        = glGetUniformLocation(program_object, "s_texture_uv");
    GLint texture_width = glGetUniformLocation(program_object, "texture_width");

    // Load the textures
    static GLuint texture_id_uv = 0;
    if (0 == texture_id_uv) {
        texture_id_uv=
            gen_texture_from_file("res/720x480.nv12.uv", width/2, height/2,
                                  GL_LUMINANCE_ALPHA);
    }
    static GLuint texture_id_y = 0;
    if (0 == texture_id_y) {
        texture_id_y =
            gen_texture_from_file("res/720x480.nv12.yuv", width, height,
                                  GL_LUMINANCE);
    }

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
      
    // Load the vertex position
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);
    // Bind the base texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_y);
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_y_loc, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_id_uv);
    // Set the base sampler to texture unit to 1
    glUniform1i(texture_uv_loc, 1);

    glUniform1f(texture_width, (GLfloat)width);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);    
}
void show_rgba(int width, int height)
{
    static GLuint program_object;
    static GLuint texture_id_rgba = 0;

    if (!program_object) {
        program_object = get_program_object_showrgba();
        void *cairo_buffer = my_cairo_draw(width, height);
        texture_id_rgba = gen_texture_from_data(
            cairo_buffer, width, height, GL_RGBA);
    }

    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_rgba_loc
        = glGetUniformLocation(program_object, "s_texture_rgba");

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
      
    // Use the program object
    glUseProgram(program_object);
    // Load the vertex position
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);
    // Bind the base texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_rgba);
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_rgba_loc, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

Matrix mvp_update ()
{
    Matrix mvpMatrix;
    Matrix perspective;
    Matrix modelview;
    float aspect;
   
    static float angle = .0f;
    angle += .5f;

    // Compute the window aspect ratio
    aspect = (GLfloat)320/(GLfloat)480;
    // Generate a perspective matrix with a 60 degree FOV
    MatrixLoadIdentity(&perspective);
    Perspective(&perspective, 60.0f, aspect, 1.0f, 20.0f);
    // Generate a model view matrix to rotate/translate the cube
    MatrixLoadIdentity(&modelview);
    // Translate away from the viewer
    Translate(&modelview, 0.0, 0.0, -2.0);
    // Rotate the cube
    Rotate(&modelview, angle, 1.0, 0.0, 1.0);
    // Compute the final MVP by multiplying the 
    // modevleiw and perspective matrices together
    MatrixMultiply(&mvpMatrix, &modelview, &perspective);

    return mvpMatrix;
}

void mvptest()
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_mvptest();
    }
    glUseProgram(program_object);

    // Get the attribute
    GLint a_position = glGetAttribLocation(program_object, "a_position");
    GLint a_color = glGetAttribLocation(program_object, "a_color");
    // Get the mvp Matrix locations
    GLint u_mvpMatrix = glGetUniformLocation(program_object, "u_mvpMatrix");

    // vertex position
    static const GLfloat vertices[] = {
        .0f, .5f, .0f,
        -.5f, -.5f, .0f,
        .5f, -.5f, .0f,
    };
	static const GLfloat colors[3][3] = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};

    /* Load the vertex data */
    glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(a_color, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(a_position);
    glEnableVertexAttribArray(a_color);

    Matrix mvpMatrix = mvp_update();
    glUniformMatrix4fv(u_mvpMatrix, 1, GL_FALSE, (GLfloat*)&mvpMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void draw_vertexs_update()
{
    static GLuint program_object;
    if (!program_object) {
        program_object = make_program_object(
            "gles/shaders/obj.vert",
            "gles/shaders/obj.frag");
    }
    glUseProgram(program_object);

    static GLfloat *verts;
    static int verts_len;
    if (!verts) {
        int load_obj_from_file(const char*, GLfloat**, int*);
        load_obj_from_file("./utils/obj/monkey.obj",
                           &verts, &verts_len);
        printf("vertices@0x%p,len=%d\n", verts, verts_len);
    }

    // Get the attribute
    GLint a_position = glGetAttribLocation(program_object, "a_position");
    GLint a_color = glGetAttribLocation(program_object, "a_color");
    // Get the mvp Matrix locations
    GLint u_mvpMatrix = glGetUniformLocation(program_object, "u_mvpMatrix");

    // vertex position
    static const GLfloat vertices[] = {
        .0f, .5f, .0f,
        -.5f, -.5f, .0f,
        .5f, -.5f, .0f,
    };
	static const GLfloat colors[3][3] = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};

    Matrix mvpMatrix = mvp_update();
    glUniformMatrix4fv(u_mvpMatrix, 1, GL_FALSE, (GLfloat*)&mvpMatrix);

    /* Load the vertex data */
    glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, verts);
    glVertexAttribPointer(a_color, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(a_position);
    glEnableVertexAttribArray(a_color);

    glDrawArrays(GL_LINE_LOOP, 0, verts_len);
}

void draw_tetrahedron()
{
    static GLuint program_object;
    if (!program_object) {
        program_object = make_program_object(
            "gles/shaders/tetrahedron.vert",
            "gles/shaders/tetrahedron.frag");
    }

    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_rgba_loc
        = glGetUniformLocation(program_object, "s_texture_rgba");

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

    // Use the program object
    glUseProgram(program_object);
    // Load the vertex position
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}
