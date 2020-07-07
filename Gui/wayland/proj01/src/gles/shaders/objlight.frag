precision mediump float;
uniform sampler2D sTexture;

varying vec2 vTextureCoord;
varying vec4 ambient;
varying vec4 diffuse;
varying vec4 specular;

void main()
{
    vec4 finalColor = texture2D(sTexture, vTextureCoord);
    gl_FragColor = finalColor*ambient + finalColor*specular + finalColor*diffuse;
}
