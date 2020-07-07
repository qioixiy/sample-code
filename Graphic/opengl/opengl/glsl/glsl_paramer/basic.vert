layout (location = 0) in  vec3 inPosition;
layout (location = 1) in  vec3 vertexTextCoord;
out vec3 texCoord;

void main(void) {
 	texCoord = vertexTextCoord;
    gl_Position = vec4(inPosition, 1.0);
}