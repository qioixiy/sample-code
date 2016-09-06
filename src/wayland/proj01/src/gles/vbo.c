
void initVertexBufferObjects(vertex_t *vertexBuffer,
                             GLushort *indices,
                             GLuint numVertices, GLuint numIndices,
                             GLuint *vboIds)
{
    glGenBuffers(2, vboIds);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertex_t),
                 vertexBuffer, GL_STATIC_DRAW);
// bind buffer object for element indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 numIndices * sizeof(GLushort),indices,
                 GL_STATIC_DRAW);
}
