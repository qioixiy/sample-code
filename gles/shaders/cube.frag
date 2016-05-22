//#extension GL_OES_EGL_image_external : require

precision mediump float;

//uniform samplerExternalOES texture;
uniform sampler2D texture;

varying float VaryingLight;
varying vec2 vVaryingTexUV;

void main()
{
    vec4 t = texture2D(texture, vVaryingTexUV);
    gl_FragColor = vec4(VaryingLight * t.rgb, 1.0);
}
