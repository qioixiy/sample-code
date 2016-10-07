precision mediump float;

uniform sampler2D s_texture_yuyv;
varying vec2 v_texCoord;
uniform float texture_width;

void main()
{
    float red, green, blue;
    vec4 luma_chroma;
    float luma, chroma_u, chroma_v;
    float pixelx, pixely;
    float xcoord, ycoord;
    float pixel_width = 1.0 / texture_width;
  
    pixelx = v_texCoord.x;
    pixely = v_texCoord.y;
      
    xcoord = floor (pixelx * texture_width);

    luma_chroma = texture2D(s_texture_yuyv, vec2(pixelx, pixely));

    // just look up the brightness
    luma = (luma_chroma.r - 0.0625) * 1.1643;
	  
    if (0.0 == mod(xcoord , 2.0)) // even
    {
        chroma_u = luma_chroma.a;
        chroma_v = texture2D(s_texture_yuyv,
                             vec2(pixelx + pixel_width, pixely)).a;
    }
    else // odd
    {
        chroma_v = luma_chroma.a;
        chroma_u = texture2D(s_texture_yuyv,
                             vec2(pixelx - pixel_width, pixely)).a;
    }

    chroma_u = chroma_u - 0.5;
    chroma_v = chroma_v - 0.5;

    /* luma = clamp(luma, 0.0, 1.0); */
    /* chroma_u = clamp(chroma_u, 0.0, 1.0); */
    /* chroma_v = clamp(chroma_v, 0.0, 1.0); */

    red = luma + 1.5958 * chroma_v;
    green = luma - 0.39173 * chroma_u - 0.81290 * chroma_v;
    blue = luma + 2.017 * chroma_u;

    gl_FragColor = vec4(red, green, blue, 1.0);
}
