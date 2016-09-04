/* ************************************************************************* 
* NAME: /home2/gpk/glutcam/callbacks.h
*
* DESCRIPTION:
*
* this is the entry point for the code in callbacks.c
*
* setup_glut_window_callbacks registers the functions that the glut
*   library will use to handle mouse clicks, keypresses, drawing
*   the window, etc
*
* PROCESS:
*
* GLOBALS:
*
* REFERENCES:
*
* LIMITATIONS:
*
* REVISION HISTORY:
*
*   STR                Description                          Author
*
*    7-Jan-07          initial coding                        gpk
*
* TARGET:  C
*
* This software is in the public domain. if it breaks you get to keep
* both pieces
*
* ************************************************************************* */


extern void setup_glut_window_callbacks(Displaydata_t * displaydata,
				       Sourceparams_t * sourceparams);
