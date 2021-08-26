// Based off ex 1
#include "CSCIx239.h"

int mode=0;    //  Shader
int th=0, ph=0; //  View angles
int fov=55;    //  Field of view (for perspective)
float asp=1;   //  Aspect ratio
float dim=3;   //  Size of world

// Shader lighting parameters
float pixelNoise[] = {0.5,0.5, 0.25,0.75, 0.75,0.25, 0.75,0.75, 0.25,0.25, 0.5,0.875, 0.5,0.125, 0.125,0.5, 0.875,0.5, 0.5,0.625, 0.5,0.375, 0.375,0.5, 0.625,0.5};
const int raysPerPixelMax = 13;
int raysPerPixel = 5;
int nPasses = 8;
float ambient = 0.3;
float roughness = 0.01;
float refractiveIndex = 1.2;

int sky = 0;

int pixW = 512, pixH = 512;
unsigned int texOut = 0;

int rayShader = 0;

//
//  Refresh display
//
void display(GLFWwindow* window)
{
   //  Identity projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glColor3f(1, 1, 1);

   float Py = 1;

   float Ex = Sin(th) * Cos(ph);
   float Ey = Py - Sin(ph);
   float Ez = -Cos(th) * Cos(ph);

   float viewMat[16];
   mat4identity(viewMat);
   mat4lookAt(viewMat, 0,Py,0, Ex,Ey,Ez, 0,1,0);
   float cameraToWorldMat[16];
   mat4invert(viewMat, cameraToWorldMat);

   float projMat[16];
   mat4identity(projMat);
   mat4perspective(projMat, fov, asp, dim / 16, 16 * dim);
   float inverseProjectionMat[16];
   mat4invert(projMat, inverseProjectionMat);

   glEnable(GL_TEXTURE_2D);

   glUseProgram(rayShader);
   glBindTexture(GL_TEXTURE_2D, sky);
   glUniform1f(glGetUniformLocation(rayShader, "time"), glfwGetTime());
   glUniform1i(glGetUniformLocation(rayShader, "skybox"), 0);
   glUniform2f(glGetUniformLocation(rayShader, "dimensions"), pixW, pixH);
   glUniform2fv(glGetUniformLocation(rayShader, "pixelNoise"), raysPerPixelMax, pixelNoise);
   glUniform1i(glGetUniformLocation(rayShader, "raysPerPixel"), raysPerPixel);
   glUniform1i(glGetUniformLocation(rayShader, "nPasses"), nPasses);
   glUniform1f(glGetUniformLocation(rayShader, "ambient"), ambient);
   glUniform1f(glGetUniformLocation(rayShader, "refrIndex"), refractiveIndex);
   glUniform1f(glGetUniformLocation(rayShader, "waterRoughness"), roughness);
   glUniformMatrix4fv(glGetUniformLocation(rayShader, "cameraToWorldMat"), 1, 0, cameraToWorldMat);
   glUniformMatrix4fv(glGetUniformLocation(rayShader, "cameraInverseProjectionMat"), 1, 0, inverseProjectionMat);
   glDispatchCompute(pixW, pixH, 1);
   glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

   glClear(GL_COLOR_BUFFER_BIT);
   glUseProgram(0);

   glBindTexture(GL_TEXTURE_2D, texOut);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex2f(-1,-1);
   glTexCoord2f(0,1); glVertex2f(-1,+1);
   glTexCoord2f(1,1); glVertex2f(+1,+1);
   glTexCoord2f(1,0); glVertex2f(+1,-1);
   glEnd();

   glDisable(GL_TEXTURE_2D);


   //  Display parameters
   glColor3f(0,0,0);
   glWindowPos2i(5, 20);
   Print("FPS: %d", FramesPerSecond());
   glWindowPos2i(5, 5);
   Print("Rays Per Pixel: %i | Passes: %i | Roughness: %.2f | Refractive Index: %.2f", raysPerPixel, nPasses, roughness, refractiveIndex);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glfwSwapBuffers(window);
}

//
//  Key pressed callback
//
void key(GLFWwindow* window,int key,int scancode,int action,int mods)
{
   int shift = !!(mods & GLFW_MOD_SHIFT);

   //  Discard key releases (keeps PRESS and REPEAT)
   if (action==GLFW_RELEASE) return;

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
     glfwSetWindowShouldClose(window,1);
   //  Reset view angle
   else if (key==GLFW_KEY_0) {
      th = ph = 0;
   }
   //  Increase/decrease asimuth
   else if (key==GLFW_KEY_RIGHT)
      th += 5;
   else if (key==GLFW_KEY_LEFT)
      th -= 5;
   //  Increase/decrease elevation
   else if (key==GLFW_KEY_UP && ph > -89)
      ph -= 5;
   else if (key==GLFW_KEY_DOWN && ph < 89)
      ph += 5;
   //  PageUp key - increase dim
   else if (key==GLFW_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key==GLFW_KEY_PAGE_UP && dim>1)
      dim -= 0.1;

   // Shader lighting parameters
   else if (key==GLFW_KEY_P && !shift && nPasses < 8) nPasses++;
   else if (key==GLFW_KEY_P && shift && nPasses > 1) nPasses--;
   else if (key==GLFW_KEY_I && !shift && refractiveIndex < 1.49) refractiveIndex += 0.05;
   else if (key==GLFW_KEY_I && shift && refractiveIndex > 1.01) refractiveIndex -= 0.05;
   else if (key==GLFW_KEY_R && !shift && raysPerPixel < raysPerPixelMax) raysPerPixel++;
   else if (key==GLFW_KEY_R && shift && raysPerPixel > 1) raysPerPixel--;
   else if (key==GLFW_KEY_G && !shift && roughness < 0.095) roughness += 0.01;
   else if (key==GLFW_KEY_G && shift && roughness > 0.005) roughness -= 0.01;

   //  Wrap angles
   th %= 360;
   ph %= 360;
   //  Update projection
   Projection(fov,asp,dim);
}

//
//  Window resized callback
//
void reshape(GLFWwindow* window,int width,int height)
{
   //  Get framebuffer dimensions (makes Apple work right)
   glfwGetFramebufferSize(window,&width,&height);
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Projection(fov,asp,dim);
}

void setupTexture()
{
   glGenTextures(1, &texOut);
   glBindTexture(GL_TEXTURE_2D, texOut);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, pixW, pixH, 0, GL_RGBA, GL_FLOAT, NULL);
   glBindImageTexture(1, texOut, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

//
//  Main program with GLFW event loop
//
int main(int argc,char* argv[])
{
   //  Initialize GLFW
   GLFWwindow* window = InitWindow("HW1: Nathan Howard",1,800,600,&reshape,&key);
   
   glfwSwapInterval(0);

   // Load shader
   rayShader = CreateShaderProgComp("rayTracer.comp");

   setupTexture();
   sky = LoadTexBMP("sky.bmp");

   //  Event loop
   ErrCheck("init");
   while(!glfwWindowShouldClose(window))
   {
      //  Display
      display(window);
      //  Process any events
      glfwPollEvents();
   }
   //  Shut down GLFW
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
}
