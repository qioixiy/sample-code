precision mediump float;

uniform sampler2D s_texture_rgba;
varying vec2 v_texCoord;

void main()
{
    vec4 argb = texture2D(s_texture_rgba, v_texCoord);
    gl_FragColor = argb;//vec4(1.0, 1.0, 1.0, 1.0);
}
