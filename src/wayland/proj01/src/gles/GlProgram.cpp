#include "GlProgram.hpp"
#include "utils/File.hpp"
#include "utils/log/Log.hpp"

GlProgram::GlProgram()
{
  ;
}

void
GlProgram::Use()
{
  ;
}

int
GlProgram::MakeProgramFromFile(string &vert, string &frag)
{
  ;
}

/**
 *
 */
int
GlProgram::MakeProgramFromString(string &vert, string &frag)
{
  GLuint vertexShader;
  GLuint fragmentShader;
  GLuint programObject;
  GLint linked;

  // Load the vertex and fragment shaders
  vertexShader = compile(GL_VERTEX_SHADER, vert.c_str());
  if (0 >= vertexShader) {
    goto Err_Vert;
  }
  fragmentShader = compile(GL_FRAGMENT_SHADER, frag.c_str());
  if (0 >= fragmentShader) {
    goto Err_Frag;
  }

  // Create the program object
  programObject = glCreateProgram();

  if (programObject == 0) {
    goto Err_glCreateProgram;
  }
  glAttachShader(programObject, vertexShader);
  glAttachShader(programObject, fragmentShader);

  // Link the program
  glLinkProgram(programObject);
  // Check the link status
  glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

  if (!linked) {

    GLint infoLen = 0;
    glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
      char* infoLog = (char*)malloc(sizeof(char) * infoLen);
      glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
      LogE << "glLinkProgram Error:%s" << infoLog;
      free(infoLog);
    }

    goto Err_glLinkProgram;
  }

  glProgramObject = programObject;
  // Free up no longer needed shader resources
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return 0;

Err_glLinkProgram:
  glDeleteProgram(programObject);

Err_glCreateProgram:
  LogE << "glCreateProgram error";
  glDeleteShader(vertexShader);

Err_Frag:
  LogE << "compile fragment shader error";
  glDeleteShader(vertexShader);

Err_Vert:
  LogE << "compile vertex shader error";
  return -1;
}

/**
 * compile shader source code
 * @param type shader type, vertex or fragment
 * @param shaderstr shader code
 * @retval if sucess will be shader id
  */
GLint
GlProgram::compile(GLenum type, const char *shaderStr)
{
  GLuint shader = 0;
  GLint compiled = 0;

  // Create the shader object
  shader = glCreateShader(type);

  if (0 == shader)///< create failed
    return -1;

  // Load the shader source
  glShaderSource(shader, 1, &shaderStr, NULL);

  // Compile the shader
  glCompileShader(shader);

  // Check the compile status
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {///< if have compile error
    GLint infoLen = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
      char* infoLog = (char*)malloc(sizeof(char) * infoLen);
      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
      LogE << "glCompileShader Error:" << infoLog;
      free(infoLog);
    }

    glDeleteShader(shader);
    return -2;///< compile error
  }

  return shader;
}
