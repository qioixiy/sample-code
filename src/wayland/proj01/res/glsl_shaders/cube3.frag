precision mediump float;

varying vec4 vVaryingColor;

uniform sampler2D s_texture_rgba;
varying vec2 v_texCoord;

void main()
{
    gl_FragColor = vVaryingColor;
    gl_FragColor = texture2D(s_texture_rgba, v_texCoord);
}
