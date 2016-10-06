#include "stdafx.h" 


#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 
#include <gl/freeglut.h> 
#include <iostream> 
#include <string>
#include <list>
#include <map>
#include <vector>
#include <malloc.h>
#include <string.h>
#include <fstream>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

//mouse motion controls
bool g_bZoom=false; // flag to run zoom actions
bool g_bRot=false; // flag to run rot actions
int g_aiLastMousePos[2]; // record of mouse position at last frame

int g_iXPos=0;
int g_iYPos=0;
int g_iXHoverPos=0;
int g_iYHoverPos=0;
unsigned int g_uiHoverCount=0;

typedef struct  
{
	int m_iId;
	float m_afPos[3];
	float m_afCol[3];
	float m_afBCol[3];
} raaVertices;

typedef struct
{
	raaVertices *m_pStart;
	raaVertices *m_pEnd;
	float m_fWeight;
} raaArc;

raaVertices *g_pHoverObj=0;

typedef std::map<int, std::string> raaNamesMap;
typedef std::map<int, raaVertices*> raaVerticesMap;
typedef std::list<raaArc*>raaArcs;

raaVertices *g_pVerticies=0;
raaNamesMap g_mNames;
raaVerticesMap g_mVertices;
raaArcs g_lArcs;
unsigned int g_uiNumVerticies;

const static float csg_fWidth=0.02f;
const static float csg_fHeight=0.01f;
const static unsigned int csg_uiMaxHover=10;

const static float csg_afOthoBase[]={-0.1f, 1.1f, -0.1f, 1.1f, 1.2f, 1.2f};
static float sg_afOthoActual[]={-0.1f, 1.1f, -0.1f, 1.1f, 1.2f, 1.2f};
static float sg_afOthoDisplay[]={-0.1f, 1.1f, -0.1f, 1.1f, 1.2f, 1.2f};
float g_afViewport[4];

const static int csg_iJitterDim=3;

raaVertices *g_pSelected=0;
float g_afSelectedOffset[2];

char ttf_buffer[1<<20];
unsigned char temp_bitmap[512*512];

stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
//GLstbtt_uint ftex;

unsigned int ftex;

void my_stbtt_initfont(void)
{
	fread(ttf_buffer, 1, 1<<20, fopen("c:/windows/fonts/times.ttf", "rb"));
	stbtt_BakeFontBitmap(data,0, 32.0, temp_bitmap,512,512, 32,96, cdata); // no guarantee this fits!
	// can free ttf_buffer at this point
	glGenTextures(1, &ftex);
	glBindTexture(GL_TEXTURE_2D, ftex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	// can free temp_bitmap at this point
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void my_stbtt_print(float x, float y, char *text)
{
	// assume orthographic projection with units = screen pixels, origin at top left
	glBindTexture(GL_TEXTURE_2D, ftex);
	glBegin(GL_QUADS);
	while (*text) {
		if (*text >= 32 && *text < 128) {
			stbtt_aligned_quad q;
			stbtt_GetBakedQuad(cdata, 512,512, *text-32, &x,&y,&q,1);//1=opengl,0=old d3d
			glTexCoord2f(q.s0,q.t1); glVertex2f(q.x0,q.y0);
			glTexCoord2f(q.s1,q.t1); glVertex2f(q.x1,q.y0);
			glTexCoord2f(q.s1,q.t0); glVertex2f(q.x1,q.y1);
			glTexCoord2f(q.s0,q.t0); glVertex2f(q.x0,q.y1);
		}
		++text;
	}
	glEnd();
}

bool jitter(int iXIn, int iYIn, int iXComp, int iYComp)
{
	if(iXIn<iXComp+csg_iJitterDim && iXIn>iXComp-csg_iJitterDim && iYIn<iYComp+csg_iJitterDim && iYIn>iYComp-csg_iJitterDim) return true;		

	return false;
}

void oglToScreen(float fXin, float fYin, int &iXOut, int &iYOut)
{
	iXOut=((int)((fXin-csg_afOthoBase[0])/csg_afOthoBase[4])*g_afViewport[2]);			
	iYOut=(int)g_afViewport[3]-((int)((fYin-csg_afOthoBase[2])/csg_afOthoBase[5])*g_afViewport[3]);			
}

void screenToOgl(int iXin, int iYin, float &fXOut, float &fYOut)
{
	float fYCor=g_afViewport[3]-(float)iYin;
	float fXCor=(float)iXin;

	fXOut=((fXCor/g_afViewport[2])*csg_afOthoBase[4])+csg_afOthoBase[0];
	fYOut=((fYCor/g_afViewport[3])*csg_afOthoBase[5])+csg_afOthoBase[2];
}

void renderArcs(bool bSelection)
{
	if(g_pVerticies)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -0.5f);

		glBegin(GL_LINES);
		for(raaArcs::iterator it=g_lArcs.begin();it!=g_lArcs.end();it++)
		{
			raaArc *pArc=(*it);
			glLineWidth(10.0f*pArc->m_fWeight);
			glColor3f(pArc->m_fWeight, pArc->m_fWeight, pArc->m_fWeight);

			glVertex3fv(pArc->m_pStart->m_afPos);
			glVertex3fv(pArc->m_pEnd->m_afPos);

		}
		glEnd();
		glPopMatrix();
	}
}

void renderVertices(bool bSelection)
{
	raaVertices *pVert=0;

	if(g_pVerticies)
	{
		glColor3f(0.1f, 0.8f, 0.2f);

		if(bSelection)
		{
			for(unsigned int i=0;i<g_uiNumVerticies;i++)
			{
				pVert=g_pVerticies+i;
				glPushName((unsigned int)pVert);
				glPushMatrix();
				glTranslatef(pVert->m_afPos[0], pVert->m_afPos[1], -0.2f);

				glBegin(GL_QUADS);
				glVertex2f(-csg_fWidth,-csg_fHeight);
				glVertex2f(csg_fWidth, -csg_fHeight);
				glVertex2f(csg_fWidth, csg_fHeight);
				glVertex2f(-csg_fWidth, csg_fHeight);
				glEnd();
				glPopName();

				glPopMatrix();
			}
		}
		else
		{
			for(unsigned int i=0;i<g_uiNumVerticies;i++)
			{
				pVert=g_pVerticies+i;
				glPushMatrix();
				glTranslatef(pVert->m_afPos[0], pVert->m_afPos[1], -0.2f);

				glBegin(GL_QUADS);
				glVertex2f(-csg_fWidth,-csg_fHeight);
				glVertex2f(csg_fWidth, -csg_fHeight);
				glVertex2f(csg_fWidth, csg_fHeight);
				glVertex2f(-csg_fWidth, csg_fHeight);
				glEnd();

				glPopMatrix();
			}
		}
	}
}
//const unsigned char *pcName[]={"Robbie"};

void renderNodeName()
{

	if(g_pHoverObj)
	{
		glPushMatrix();
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		float fX, fY;
		screenToOgl(g_iXPos, g_iYPos, fX, fY);

		my_stbtt_print(fX, fY, "Robbie");


//		glRasterPos2f(0.5f, 0.5f);
//		glutBitmapS

		//		glTranslatef(fX, fY, -0.1f);
//		glTranslatef(0.5f, 0.5f, -0.1f);
//		glTranslatef(-0.01f, -0.01f, 0.0f);


//		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)g_mNames[g_pHoverObj->m_iId].c_str());
//		glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char*)g_mNames[g_pHoverObj->m_iId].c_str());
//		glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char*)"Robbie");
//		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'R');
//		glutStrokeCharacter(GLUT_STROKE_ROMAN, g_mNames[g_pHoverObj->m_iId].c_str());

		glPopMatrix();
		glPushMatrix();

		glTranslatef(fX, fY, -0.1f);
		glTranslatef(-0.01f, -0.01f, 0.0f);
		glBegin(GL_QUADS);
		glVertex2f(-csg_fWidth,-csg_fHeight);
		glVertex2f(csg_fWidth, -csg_fHeight);
		glVertex2f(csg_fWidth, csg_fHeight);
		glVertex2f(-csg_fWidth, csg_fHeight);
		glEnd();

		glPopMatrix();
	}
/*
	glPushMatrix();
	{
		glTranslatef(0.0, 7.0, 0.0);

		for (int i = 0; i < 128; i += 16)
		{
			glPushMatrix();
			{
				for (int j = i; j < i + 16; j++)
					draw_glyph(j);
			}
			glPopMatrix();

			glTranslatef(0.0, -1.0, 0.0);
		}
	}
	glPopMatrix();
	*/
}

raaVertices* select(int iX, int iY)
{
	int aiViewport[4];
	unsigned int auiSelectBuffer[1000]; 
	glGetIntegerv(GL_VIEWPORT, aiViewport);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix(iX, aiViewport[3]-iY, 3,3, aiViewport);
	gluOrtho2D(csg_afOthoBase[0], csg_afOthoBase[1], csg_afOthoBase[2], csg_afOthoBase[3]);
	glMatrixMode(GL_MODELVIEW);

	glInitNames();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -0.2f);

	glSelectBuffer(1000, auiSelectBuffer);
	glRenderMode(GL_SELECT);
	renderVertices(true);
	unsigned int uiNumHits=glRenderMode(GL_RENDER);	

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	if(uiNumHits) 
	{
		unsigned int uiMinZ=0xffffffff;
		unsigned int uiHit=0;
		unsigned int *pRecord=auiSelectBuffer;

		for(unsigned int i=0;i<uiNumHits;i++)
		{
			if(pRecord[0])
			{
				if(pRecord[1]<uiMinZ)
				{ 
					uiMinZ=pRecord[1];
					uiHit=pRecord[3];
				}
				pRecord+=pRecord[0]+3;
			}
			else pRecord+=3;
		}

		return (raaVertices*)uiHit;
	}
	return 0;
}

void display()
{
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -0.2f);
		
	renderVertices(false);
	renderArcs(false);
	renderNodeName();
	
	glFlush(); 
	glutSwapBuffers();
}

void idle()
{
	if(jitter(g_iXPos, g_iYPos, g_iXHoverPos, g_iYHoverPos)) g_uiHoverCount++;

	if(g_uiHoverCount>csg_uiMaxHover)
	{
//		if(!g_pHoverObj) g_pHoverObj=select(g_iXPos, g_iYPos);
		g_pHoverObj=select(g_iXPos, g_iYPos);
	}
	else g_pHoverObj=0;

	g_iXHoverPos=g_iXPos;
	g_iYHoverPos=g_iYPos;

	glutPostRedisplay();
}

void reshape(int iWidth, int iHeight)
{
	g_afViewport[0]=0.0f;
	g_afViewport[1]=0.0f;
	g_afViewport[2]=(float)iWidth;
	g_afViewport[3]=(float)iHeight;

	float fAspect=1.0f;
	float fAspectInv=1.0f;

	if(iWidth>iHeight)
	{
		fAspect=((float)iHeight)/((float)iWidth);	
		fAspectInv=1.0f/fAspect;

		float fWidth=csg_afOthoBase[5]*fAspectInv;


//		sg_afOthoActual[4]=fAspectInv*csg_afOthoBase[4];
	}
	else
	{
		fAspect=((float)iHeight)/((float)iWidth);	
		fAspectInv=1.0f/fAspect;
	}

	glViewport(0, 0, iWidth, iHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(csg_afOthoBase[0], csg_afOthoBase[1], csg_afOthoBase[2], csg_afOthoBase[3]);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void keyboard(unsigned char c, int iXPos, int iYPos)
{
}

void sKeyboard(int iC, int iXPos, int iYPos)
{
}

void mouse(int iKey, int iEvent, int iXPos, int iYPos)
{
	if(iKey==GLUT_RIGHT_BUTTON && iEvent==GLUT_DOWN) 
	{
		g_pSelected=select(iXPos, iYPos);			

		if(g_pSelected)
		{
			float fSX, fSY;

			screenToOgl(iXPos, iYPos, fSX, fSY);

			g_afSelectedOffset[0]=g_pSelected->m_afPos[0]-fSX;
			g_afSelectedOffset[1]=g_pSelected->m_afPos[1]-fSY;
		}	
	}
	else if(iKey==GLUT_RIGHT_BUTTON && iEvent==GLUT_UP)  g_pSelected=0;
}

void idleMotion(int iXPos, int iYPos)
{
	g_iXPos=iXPos;
	g_iYPos=iYPos;
//	g_uiHoverCount=0;
	glutPostRedisplay();
}

void motion(int iXPos, int iYPos)
{
	if(g_pSelected)
	{
		float fSX, fSY;
		screenToOgl(iXPos, iYPos, fSX, fSY);
		g_pSelected->m_afPos[0]=fSX+g_afSelectedOffset[0];
		g_pSelected->m_afPos[1]=fSY+g_afSelectedOffset[1];
	}
}

/*
void menuMain(int i)
{
}

void menuDisplay(int i)
{
	g_iRenderMode=i;

	// print out the current mode
	switch(g_iRenderMode)
	{
	case 1:
		std::cout << "You have selected mode " << g_iRenderMode << " Fill" << std::endl;	
		break;
	case 2:
		std::cout << "You have selected mode " << g_iRenderMode << " Points" << std::endl;	
		break;
	case 3:
		std::cout << "You have selected mode " << g_iRenderMode << " Lines" << std::endl;	
		break;
	}


	glutPostRedisplay();
}
*/

void myInit()
{
	stbtt_fontinfo font;
	unsigned char *bitmap;
//	int w,h,i,j,c = (argc > 1 ? atoi(argv[1]) : 'a'), s = (argc > 2 ? atoi(argv[2]) : 20);

	fread(ttf_buffer, 1, 1<<25, fopen(argc > 3 ? argv[3] : "c:/windows/fonts/arialbd.ttf", "rb"));

	stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer,0));
	bitmap = stbtt_GetCodepointBitmap(&font, 0,stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0,0);

	for (j=0; j < h; ++j) {
		for (i=0; i < w; ++i)
			putchar(" .:ioVM@"[bitmap[j*w+i]>>5]);
		putchar('\n');
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void vertices(std::string sString, int iIndex)
{
	std::string sColour;
	std::string sBColour;

	raaVertices *pVert=g_pVerticies+iIndex;

	if(sString.length())
	{
		char *pStr=(char*)_alloca(sizeof(char)*sString.length()+1);
		sprintf(pStr, "%s", sString.c_str());

		char *pPos=strtok(pStr, " \"");

		pVert->m_iId=pPos ? atoi(pPos) : 0;
		g_mNames[(unsigned long)pVert]=(pPos=strtok(0, "\"")) ? pPos : "";
		pVert->m_afPos[0]=(pPos=strtok(0, " ")) ? atof(pPos) : 0.0f;
		pVert->m_afPos[1]=(pPos=strtok(0, " ")) ? atof(pPos) : 0.0f;
		pVert->m_afPos[2]=(pPos=strtok(0, " ")) ? atof(pPos) : 0.0f;
		pPos=strtok(0, " ");
		sColour=(pPos=strtok(0, " ")) ? pPos : "default";
		pPos=strtok(0, " ");
		sBColour=(pPos=strtok(0, " ")) ? pPos : "default";
	
		g_mVertices[pVert->m_iId]=pVert;
	}
}

void normaliseArcWeights()
{
	float fMax, fMin;
	bool bFirst=true;

	for(raaArcs::iterator it=g_lArcs.begin();it!=g_lArcs.end();it++)
	{
		raaArc *pArc=*it;

		if(bFirst)
		{
			fMax=fMin=pArc->m_fWeight;
			bFirst=false;
		}

		if(pArc->m_fWeight>fMax) fMax=pArc->m_fWeight;
		if(pArc->m_fWeight<fMin) fMin=pArc->m_fWeight;
	}

	for(raaArcs::iterator it=g_lArcs.begin();it!=g_lArcs.end();it++)
	{
		raaArc *pArc=*it;
		pArc->m_fWeight=1.0f-((((pArc->m_fWeight-fMin)/(fMax-fMin))*0.95f)+0.05f);
	}
}


void arc(std::string sString)
{
	if(sString.length())
	{
		raaArc *pArc=new raaArc();
		char *pStr=(char*)_alloca(sizeof(char)*sString.length()+1);
		sprintf(pStr, "%s", sString.c_str());

		char *pPos=strtok(pStr, " ");
		pArc->m_pStart=pPos ? ((g_mVertices.find(atoi(pPos))!=g_mVertices.end()) ? g_mVertices[atoi(pPos)] : 0)  : 0;
		pArc->m_pEnd=(pPos=strtok(0, " ")) ? ((g_mVertices.find(atoi(pPos))!=g_mVertices.end()) ? g_mVertices[atoi(pPos)] : 0)  : 0;
		pArc->m_fWeight=(pPos=strtok(0, " ")) ? atof(pPos) : 0.0f;

		if(pArc->m_pStart && pArc->m_pEnd) g_lArcs.push_back(pArc);
	}
}

bool loadPajek(std::string sFile)
{
	std::string sLine;
	std::ifstream in(sFile);
	int iMode=0; // 1->vertices, 2->arcs; 	

	g_mNames.clear();
	g_mVertices.clear();
	g_lArcs.clear();
	if(g_pVerticies) delete [] g_pVerticies;

	if(in.is_open())
	{
		while(!in.eof())
		{
			std::getline(in, sLine);

			if(sLine.find("*Vertices")!=std::string::npos) iMode=1;
			else if(sLine.find("*Arcs")!=std::string::npos) iMode=2;

			switch(iMode)
			{
				case 1:
					{
						char *pLine=(char*)_alloca(sizeof(char)*sLine.length()+1);
						sprintf(pLine, "%s", sLine.c_str());

						char *pPos=strtok(pLine, " ");
						g_uiNumVerticies=(pPos=strtok(0," ")) ? atoi(pPos) : 0;
						g_pVerticies=new raaVertices[g_uiNumVerticies];	

						for(int i=0;i<g_uiNumVerticies;i++)
						{
							std::getline(in, sLine);
							vertices(sLine, i);
						}
					}
					break;
				case 2:
					arc(sLine);
					break;
			}
		}
		in.close();
		normaliseArcWeights();
		return true;
	}	
	return false;
}

int main(int argc, char* argv[])
{

	for(int i=0;i<argc;i++) if(!strcmp(argv[i], "-f")) loadPajek(argv[i+1]);

	glutInit(&argc, (char**)argv); 

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(512,512);
	glutCreateWindow("raaGraphToolOGL");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape); 
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(sKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(idleMotion);
/*
	g_iDisplayMenu= glutCreateMenu(menuDisplay);

	glutAddMenuEntry("Show fill",1);
	glutAddMenuEntry("Show points", 2);
	glutAddMenuEntry("Show lines", 3);

	g_iMainMenu= glutCreateMenu(menuMain); // create a menu and associate a handler function

	// add sub menu to main menu 
	glutAddSubMenu("Display", g_iDisplayMenu);

	// add quit action to main window
	glutAddMenuEntry("Quit",1);

	// attach menus to a mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
*/

	myInit();

	glutMainLoop();
	return 0;
}

