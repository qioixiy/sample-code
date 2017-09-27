//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// Hello_Triangle.c
//
//    This is a simple example that draws a single triangle with
//    a minimal vertex/fragment shader.  The purpose of this 
//    example is to demonstrate the basic concepts of 
//    OpenGL ES 2.0 rendering.
#include <stdlib.h>
#include "esUtil.h"

// uniforms used by the vertex shader
uniform mat4
u_mvpMatrix; // matrix to convert P from model
// space to normalized device space.
// attributes input to the vertex shader
attribute vec4
a_position; // position value
attribute vec4
a_color;
// input vertex color
// varying variables – input to the fragment shader
varying vec4
v_color;
// output vertex color
	void
main()
{
	v_color = a_color;
	gl_Position = u_mvpMatrix * a_position;
	printf("Vertex_Shader\n");

}
