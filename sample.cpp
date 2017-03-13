// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <math.h>

#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();

	double torsoRadius = VAL(TORSORADIUS);
	double torsoHeight = VAL(TORSOHEIGHT);
	double upperArmLength = VAL(UPPERARMLENGTH);
	double lowerBodyHeight = VAL(LOWERBODYHEIGHT);
	double headSize = VAL(HEAD_SCALE);

	// draw the floor
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5, 0, -5);
	drawBox(10, 0.01f, 10);
	glPopMatrix();

	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
		//torso
		glPushMatrix();
			//upper body
			glPushMatrix();
			// TODO: change 2.25 to control value (lower body height)
			glTranslated(-torsoRadius, lowerBodyHeight, 0);
			glScaled(2.0 * torsoRadius, torsoHeight, torsoRadius);
			drawBox(1, 1, 1);
			glPopMatrix();

			//head
			glPushMatrix();
			glTranslated(0, lowerBodyHeight + VAL(HEAD_Y) + torsoHeight, 0.5);
			glScaled(headSize, headSize, headSize);
			glTranslated(0, headSize, 0);
			glRotated(-90, 1.0, 0.0, 0.0);
			drawSphere(1);
			glPopMatrix();

			//left arm
			glPushMatrix();
			//shoulder
			glTranslated(-1.8 * torsoRadius, lowerBodyHeight + 0.6 * torsoHeight, 0);
			glScaled(0.8 * torsoRadius, 0.8 * torsoRadius, 0.8 * torsoRadius);
			drawBox(1, 1, 1);
			//left upper arm
			glTranslated(0.05, -upperArmLength, 0.15);
			glScaled(0.72 * torsoRadius, upperArmLength, 0.72 * torsoRadius);
			drawBox(1, 1, 1);
			//left lower arm
			glTranslated(0.05, -0.8 * upperArmLength, 0.15);
			glScaled(0.648 * torsoRadius, 0.8 * upperArmLength, 0.648 * torsoRadius);
			drawBox(1, 1, 1);
			glPopMatrix();

			//right arm
			glPushMatrix();
			//shoulder
			glTranslated(torsoRadius, lowerBodyHeight + 0.6 * torsoHeight, 0);
			glScaled(0.8 * torsoRadius, 0.8 * torsoRadius, 0.8 * torsoRadius);
			drawBox(1, 1, 1);
			//right upper arm
			glTranslated(0.1, -upperArmLength, 0.15);
			glScaled(0.72 * torsoRadius, upperArmLength, 0.72 * torsoRadius);
			drawBox(1, 1, 1);
			//right lower arm
			glTranslated(0.1, -0.8 * upperArmLength, 0.15);
			glScaled(0.648 * torsoRadius, 0.8 * upperArmLength, 0.648 * torsoRadius);
			drawBox(1, 1, 1);
			glPopMatrix();

		glPopMatrix();
		//lower torso
		glPushMatrix();
		glTranslated(0, lowerBodyHeight - 0.1, 0.5 * torsoRadius);
			glPushMatrix();
			glScaled(torsoRadius, 0.1, 0.5 * torsoRadius);
			glRotated(-90, 1.0, 0.0, 0.0);
			drawCylinder(1, 1, 1);
			glPopMatrix();
			//left leg
			glPushMatrix();
				glTranslated(-torsoRadius / 1.7, -0.45 * lowerBodyHeight, 0);
				glPushMatrix();
					glScaled(torsoRadius / 2.5, 0.45 * lowerBodyHeight, torsoRadius / 2.5);
					glRotated(-90, 1.0, 0.0, 0.0);
					//left upper leg
					drawCylinder(1, 1, 1);
					//left lower leg
					glTranslated(0, 0, -0.45 * lowerBodyHeight);
					glScaled(0.8, 1, 1.5);
					drawCylinder(1, 1, 1);
				glPopMatrix();
				//left foot
				glTranslated(-torsoRadius / 2.0, -0.5 * lowerBodyHeight, -torsoRadius / 2.0);
				glScaled(1, 0.4, 1.35);
				drawBox(1, 1, 1);
			glPopMatrix();
			//right leg
			glPushMatrix();
				glTranslated(torsoRadius / 1.7, -0.45 * lowerBodyHeight, 0);
				glPushMatrix();
					glScaled(torsoRadius / 2.5, 0.45 * lowerBodyHeight, torsoRadius / 2.5);
					glRotated(-90, 1.0, 0.0, 0.0);
					//right upper leg
					drawCylinder(1, 1, 1);
					//right lower leg
					glTranslated(0, 0, -0.45 * lowerBodyHeight);
					glScaled(0.8, 1, 1.5);
					drawCylinder(1, 1, 1);
				glPopMatrix();
				//right foot
				glTranslated(-torsoRadius / 2.0, -0.5 * lowerBodyHeight, -torsoRadius / 2.0);
				glScaled(1, 0.4, 1.35);
				drawBox(1, 1, 1);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	/*
	// draw the sample model
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		//body
		glPushMatrix();
		glTranslated(-0.5, 2.25, -0.5);
		glScaled(1, 1.5, 1);
		drawBox(1, 1, 1);
		glPopMatrix();

		//head
		glPushMatrix();
		glTranslated(0, 3.75, 0);
		glScaled(VAL(HEAD_SCALE), VAL(HEAD_SCALE), VAL(HEAD_SCALE));
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(1, 1, 1);
		glPopMatrix();

		//rightArm
		//shoulder
		glPushMatrix();
		glTranslated(-0.75, 3.5, 0);
		drawSphere(0.25);
			//uArm
			glPushMatrix();
			glTranslated(-0.25, -0.75, -0.25);
			glScaled(0.5, 0.75, 0.5);
			drawBox(1, 1, 1);
			glPopMatrix();
		//elbow
		glTranslated(0, -0.85, 0);
		drawSphere(0.25);
		//lArm
		glTranslated(-0.25, -0.85, -0.25);
		glScaled(0.5, 0.75, 0.5);
		drawBox(1, 1, 1);
		glPopMatrix();

		//leftArm
		//shoulder
		glPushMatrix();
		glTranslated(0.75, 3.5, 0);
		drawSphere(0.25);
			//uArm
			glPushMatrix();
			glTranslated(-0.25, -0.75, -0.25);
			glScaled(0.5, 0.75, 0.5);
			drawBox(1, 1, 1);
			glPopMatrix();
		//elbow
		glTranslated(0, -0.85, 0);
		drawSphere(0.25);
		//lArm
		glTranslated(-0.25, -0.85, -0.25);
		glScaled(0.5, 0.75, 0.5);
		drawBox(1, 1, 1);
		glPopMatrix();
	
		//lowerBody
		glPushMatrix();
		glTranslated(0, 2.15, 0);
			glPushMatrix();
			glScaled(0.5, 0.1, 0.5);
			glRotated(-90, 1.0, 0.0, 0.0);
			drawCylinder(1, 1, 1);
			glPopMatrix();
			//glPopMatrix();

			//leftLeg
			//uArm
			glPushMatrix();
			//ankle
			glTranslated(-0.25, -0.1, 0);
			drawSphere(0.25);
				//lArm
				glPushMatrix();
				glTranslated(-0.25, -1.1, -0.25);
				glScaled(0.45, 1, 0.45);
				drawBox(1, 1, 1);
				glPopMatrix();
			//elbow
			glTranslated(0, -1.1, 0);
			drawSphere(0.25);
			//lArm
			glTranslated(-0.25, -0.9, -0.25);
			glScaled(0.45, 0.75, 0.45);
			drawBox(1, 1, 1);
			glPopMatrix();



			//rightLeg
			//uArm
			glPushMatrix();
			//ankle
			glTranslated(0.25, -0.1, 0);
			drawSphere(0.25);
			//lArm
				glPushMatrix();
				glTranslated(-0.25, -1.1, -0.25);
				glScaled(0.45, 1, 0.45);
				drawBox(1, 1, 1);
				glPopMatrix();
			//elbow
			glTranslated(0, -1.1, 0);
			drawSphere(0.25);
			//lArm
			glTranslated(-0.25, -0.9, -0.25);
			glScaled(0.45, 0.75, 0.45);
			drawBox(1, 1, 1);
			glPopMatrix();
	
		glPopMatrix();
		//lowerBodyEnd
	glPopMatrix();
	*/
	/*
	// draw cannon
	glPushMatrix();
	glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawCylinder(VAL(HEIGHT), 0.1, 0.1);

	glTranslated(0.0, 0.0, VAL(HEIGHT));
	drawCylinder(1, 1.0, 0.9);

	glTranslated(0.0, 0.0, 0.5);
	glRotated(90, 1.0, 0.0, 0.0);
	drawCylinder(4, 0.1, 0.2);
	glPopMatrix();
	*/	
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[TORSOHEIGHT] = ModelerControl("Torso Height", 2.0f, 3.0f, 0.1f, 2.0f);
	controls[TORSORADIUS] = ModelerControl("Torso Radius", 0.75f, 1.25f, 0.05f, 1.0f);
	controls[UPPERARMLENGTH] = ModelerControl("Upper arm length", 1.0f, 1.75f, 0.05f, 1.2f);
	controls[LOWERBODYHEIGHT] = ModelerControl("Lower body height", 2.25f, 4.0f, 0.25f, 2.25f);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[HEAD_SCALE] = ModelerControl("Scale Head", 0, 1, 0.05f, 0.5f);
	controls[HEAD_Y] = ModelerControl("Head Y Pos", 0.0f, 0.75f, 0.05f, 0.25f);
    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
