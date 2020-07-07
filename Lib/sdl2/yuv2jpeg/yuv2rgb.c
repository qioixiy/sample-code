void yuv_to_rgb(  unsigned char * src[3],  // yuv420
      int stride_s,     // stride of lum, assume strides of U,V are stride_s/2
      int W,       // width, assume W%2 == 0
      int H,       // height, assume H%2 == 0
      unsigned char* _dst    // rgb32
    )
{
 unsigned char * pY = src[0];
 unsigned char * pU = src[1];
 unsigned char * pV = src[2];
 unsigned char * outbuf = _dst;
 int    stride = stride_s;
 int    width = W, height = H;
 int    i,j,k,y,u,v,r,g,b,rdif,invgdif,bdif;
 int    YPOS,UPOS,VPOS;

 YPOS = UPOS= VPOS = 0;
 for(i=0; i<height; i++)
 {
  for (j=0; j<width; j++)
  {
   k = 0;
   y = pY[YPOS];
   u = pU[UPOS] - 128;
   v = pV[VPOS] - 128;
   
   rdif = v + ((v * 103) >> 8);
   invgdif = ((u * 88) >> 8) +((v * 183) >> 8);
   bdif = u +( (u*198) >> 8);
   
   r = y + rdif;
   g = y - invgdif;
   b = y + bdif;

   r=r>255?255:(r<0?0:r);
   g=g>255?255:(g<0?0:g);
   b=b>255?255:(b<0?0:b);

   outbuf[(i*width + j)*3 + k++] = b;
   outbuf[(i*width + j)*3 + k++] = g;
   outbuf[(i*width + j)*3 + k++] = r;
   outbuf[(i*width + j)*3 + k++] = 0xff;

   YPOS++;     
   if(j & 0x01)  //u,v?????y
   {
	   UPOS++;
	   VPOS++;     
   }
  }
  if((i & 0x01)== 0)  //u,v?????y
  {
	  UPOS -= width>>1;
	  VPOS -= width>>1;
  }
 } 
}
