precision mediump float;

uniform sampler2D s_texture_rgba;
varying vec2 v_texCoord;

void main()
{
    vec4 argb = texture2D(s_texture_rgba, v_texCoord);
    // gles default don't known how to handle when have alpha value
    // so discard it
    if(argb.a < 0.000001)
        discard;
    gl_FragColor = argb;//vec4(1.0, 1.0, 1.0, 1.0);
}
