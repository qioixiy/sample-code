#include "cgl.h"

CGL::CGL()
{
    //ctor

}

CGL::CGL(int _width, int _height)
{
    this->width = _width;
    this->height = _height;

   // model = mat4(0.5f);

    prog = ShaderProgram();

}

CGL::~CGL()
{
    //dtor
}

bool CGL::initGL()
{
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Depth buffer setup */
    glClearDepth( 1.0f );
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    model = mat4(1.0f);
    view = glm::lookAt(vec3(-2.0f,5.0f,1.0f), vec3(0.0f,1.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    bunny = ObjObject("assets/model/cubic.obj");
    return( true );
}



bool CGL::resizeGL(int width,int height)
{
    if ( height == 0 )
    {
        height = 1;
    }
    //Reset View
    glViewport( 0, 0, (GLint)width, (GLint)height );
    //Choose the Matrix mode
    glMatrixMode( GL_PROJECTION );
    //reset projection
    glLoadIdentity();
    //set perspection
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    //choose Matrix mode
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
}

bool CGL::renderGL()
{
    /* These are to calculate our fps */
    static GLint T0     = 0;
	static GLint Frames = 0;
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */

    glMatrixMode( GL_MODELVIEW );

    glDrawArrays(GL_TRIANGLES, 0, bunny.vertices.size() );

   	SDL_GL_SwapBuffers( );


    //this->changeMatrics();
    /* Gather our frames per second */
    Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
        }
    }
}



void CGL::compileShader()
{


	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, bunny.vertices.size() * sizeof(glm::vec3), &bunny.vertices[0], GL_STATIC_DRAW);

// 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

// 2rd attribute buffer : normals
    GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, bunny.normals.size() * sizeof(glm::vec3), &bunny.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(
        1,                                // attribute
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

// 3rd attribute buffer : uvs
    GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, bunny.uvs.size() * sizeof(glm::vec2), &bunny.uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
    );

// 4rd attribute buffer : tangents
    GLuint tangentbuffer;
	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, bunny.tangents.size() * sizeof(glm::vec3), &bunny.tangents[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
    glVertexAttribPointer(
        3,                                // attribute
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

// 5rd attribute buffer : bitangents
    GLuint bitangentbuffer;
	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, bunny.bittangents.size() * sizeof(glm::vec3), &bunny.bittangents[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
    glVertexAttribPointer(
        4,                                // attribute
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );



    if( ! prog.compileShaderFromFile("shader/basic.vert",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/basic.frag",GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }

    prog.bindAttribLocation(0, "VertexPosition");
    prog.bindAttribLocation(1, "VertexNormal");

    if( ! prog.link() )
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.validate() )
    {
        printf("Program failed to validate!\n%s",
               prog.log().c_str());
        exit(1);
    }
    prog.use();
}

void CGL::changeMatrics()
{
    this->model = glm::rotate(this->model, 1.0f, vec3(0.0f,1.0f,0.0f));
    mat4 mv = view * model;
    mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    prog.setUniform("MVP", projection * mv);
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
}

void CGL::setUniform()
{
    //model = glm::rotate(this->model, 10.0f, vec3(0.0f,1.0f,0.0f));
    mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 mv = view * model;
    mat3 normalMatrix = mat3( vec3(view[0]), vec3(view[1]), vec3(view[2]) );

   //
    prog.setUniform("Material.Kd", 1.0f, 1.0f, 0.5f);
    prog.setUniform("Material.Ka", 1.0f, 1.0f, 0.5f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Shininess", 1000.0f);

    vec4 lightPos = vec4(1.0f, 5.0f, 20.0f, 1.0f);
    prog.setUniform("Light.position", view * lightPos);
    prog.setUniform("Light.intensity", vec3(0.9f,0.9f,0.9f) );

    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",normalMatrix);
    prog.setUniform("MVP", projection * mv);

}

void CGL::clean()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &vertexbuffer);
	prog.deleteProgram();
	glDeleteVertexArrays(1, &VertexArrayID);
}

bool CGL::loadTexture()
{
    int mode;
    GLuint texIDs[2];
    glGenTextures(2, texIDs);
    // Load brick brake file
    const char * texName = "assets/textures/crate.bmp";
    SDL_Surface* surface = IMG_Load(texName);
    SDL_SetAlpha(surface, SDL_SRCALPHA, 0);
    if (surface==NULL) { //If it failed, say why and don't continue loading the texture
        cout<<"Error:" <<SDL_GetError()<<endl;
        return 0;
    }

    // work out what format to tell glTexImage2D to use...
    if (surface->format->BytesPerPixel == 3) { // RGB 24bit
        mode = GL_RGB;
    } else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit
        mode = GL_RGBA;
    } else {
        SDL_FreeSurface(surface);
        return 0;
    }

    // Copy file to OpenGL
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texIDs[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w,surface->h, 0, mode,GL_UNSIGNED_BYTE,surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load moss texture file
    texName = "assets/textures/smile.png";
    surface = IMG_Load(texName);
    SDL_SetAlpha(surface, SDL_SRCALPHA, 0);
    if (surface==NULL) { //If it failed, say why and don't continue loading the texture
        cout<<"Error:" <<SDL_GetError()<<endl;
        return 0;
    }

    // work out what format to tell glTexImage2D to use...
    if (surface->format->BytesPerPixel == 3) { // RGB 24bit
        mode = GL_RGB;
    } else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit
        mode = GL_RGBA;
    } else {
        SDL_FreeSurface(surface);
        return 0;
    }

    // Copy file to OpenGL
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texIDs[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w,surface->h, 0, mode,GL_UNSIGNED_BYTE,surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(surface) SDL_FreeSurface(surface);

    prog.setUniform("Tex1", 0);
    prog.setUniform("Tex2", 1);
    return true;
}

bool CGL::fileExists( const string & fileName )
{
    struct stat info;
    int ret = -1;

    ret = stat(fileName.c_str(), &info);
    return 0 == ret;
}
