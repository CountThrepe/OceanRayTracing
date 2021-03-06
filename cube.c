#include "CSCIx239.h"
//
//  Draw a cube
//

//
//  Solid unit cube
//
void SolidCube()
{
   //  Set colors
   float color[][4] = {{0,0,0,0},{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,1,0},{1,0,1,0},{1,1,1,1}};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,32.0);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color[7]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,color[0]);

   //  Front
   glColor4fv(color[1]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color[1]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color[1]);
   glNormal3f( 0, 0, 1);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   glEnd();

   //  Back
   glColor4fv(color[2]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color[2]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color[2]);
   glNormal3f( 0, 0,-1);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();

   //  Right
   glColor4fv(color[3]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color[3]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color[3]);
   glNormal3f(+1, 0, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();

   //  Left
   glColor4fv(color[4]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color[4]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color[4]);
   glNormal3f(-1, 0, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();

   //  Top
   glColor4fv(color[5]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color[5]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color[5]);
   glNormal3f( 0,+1, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();

   //  Bottom
   glColor4fv(color[6]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color[6]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color[6]);
   glNormal3f( 0,-1, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
}

void MultiTexturedCube(int tex1, int tex2, int tex3, int tex4, int tex5, int tex6)
{
   //  Set colors
   float color[][4] = {{0,0,0,0},{1,1,1,1}};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,32.0);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color[1]);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,color[0]);
   glColor4fv(color[1]);

   //  Front
   glBindTexture(GL_TEXTURE_2D, tex2);
   glNormal3f( 0, 0,-1);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
   glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
   glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
   glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
   glEnd();

   //  Back
   glBindTexture(GL_TEXTURE_2D, tex4);
   glNormal3f( 0, 0, 1);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
   glEnd();

   //  Right
   glBindTexture(GL_TEXTURE_2D, tex3);
   glNormal3f(-1, 0, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
   glEnd();

   //  Left
   glBindTexture(GL_TEXTURE_2D, tex5);
   glNormal3f( 1, 0, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();

   //  Top
   glBindTexture(GL_TEXTURE_2D, tex6);
   glNormal3f( 0,-1, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
   glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
   glEnd();

   //  Bottom
   glBindTexture(GL_TEXTURE_2D, tex1);
   glNormal3f( 0, 1, 0);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
   glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
   glEnd();
}

//
//  Textured unit cube
//
void TexturedCube(int tex)
{
   //  Draw with texture
   if (tex)
   {
      glBindTexture(GL_TEXTURE_2D,tex);
      glEnable(GL_TEXTURE_2D);
      SolidCube();
      glDisable(GL_TEXTURE_2D);
   }
   //  Draw without texture
   else
      SolidCube();
}

void Skybox(int tex0, int tex1, int tex2, int tex3, int tex4, int tex5, float radius)
{
   glPushMatrix();
   glScaled(radius, radius, radius);
   glEnable(GL_TEXTURE_2D);
   MultiTexturedCube(tex0, tex1, tex2, tex3, tex4, tex5);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

//
//  General cube
//
void Cube(float x,float y,float z , float dx,float dy,float dz, float th,float ph , int tex)
{

   //  Transform
   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Draw textured cube
   TexturedCube(tex);
   // Restore
   glPopMatrix();
}
