#include "stdafx.h"
#include "OpenGLControl.h"


COpenGLControl::COpenGLControl(void)
{
   m_fPosX = 0.0f;    // X position of model in camera view
   m_fPosY = 0.0f;    // Y position of model in camera view
   m_fZoom = 10.0f;   // Zoom on model in camera view
   m_fRotX = 45.0f;    // Rotation on model in camera view
   m_fRotY = -45.0f;    // Rotation on model in camera view
}

COpenGLControl::~COpenGLControl(void)
{
}

void COpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
   CString className = AfxRegisterWndClass(CS_HREDRAW |
      CS_VREDRAW | CS_OWNDC, NULL,
      (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

   CreateEx(0, className, _T("OpenGL"), WS_CHILD | WS_VISIBLE |
            WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

   // Set initial variables' values
   //m_oldWindow    = rect;
   //m_originalRect = rect;

   hWnd = parent;
}

void COpenGLControl::oglInitialize(void)
{
   // Initial Setup:
   //
   static PIXELFORMATDESCRIPTOR pfd =
   {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      32,    // bit depth
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      16,    // z-buffer depth
      0, 0, 0, 0, 0, 0, 0,
   };

   // Get device context only once.
   hdc = GetDC()->m_hDC;
   // Pixel format.
   m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
   SetPixelFormat(hdc, m_nPixelFormat, &pfd);
   // Create the OpenGL Rendering Context.
   hrc = wglCreateContext(hdc);
   wglMakeCurrent(hdc, hrc);

   // Basic Setup:
   //
   // Set color to use when clearing the background.
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);
   // Turn on backface culling
   glFrontFace(GL_CCW);
   glCullFace(GL_BACK);
   // Turn on depth testing
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

	// Setup Light
	GLfloat ambient[] = { 0.2f, 0.2f, 0.2f};
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f};
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f};
	GLfloat position0[] = { 1.0f, 1.0f, 1.0f, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_NORMALIZE);

   // Send draw request
   OnDraw(NULL);
}

void COpenGLControl::oglDrawScene(void)
{
	// Clear color and depth buffer bits
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat mat_color[] = { 1.0, 1.0, 0.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);

	GLUquadric *quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);

	glPushMatrix();
	gluCylinder(quadric, 1.0, 1.0, 1.0, 50, 10);
	glTranslatef(2.0, 1.5, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(quadric, 1.0, 1.0, 1.0, 50, 10);
	glPopMatrix();

	//glutSolidCube (1.0);
	//glutSolidSphere(1.0, 50, 50);
	//glutSolidCone(1.0, 1.0, 50, 1);

	// Swap buffers
	SwapBuffers(hdc);
}

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void COpenGLControl::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	ValidateRect(NULL);
}

int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CWnd::OnCreate(lpCreateStruct) == -1)
      return -1;

   oglInitialize();

   return 0;
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
   CWnd::OnSize(nType, cx, cy);

   if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

   // Map the OpenGL coordinates.
   glViewport(0, 0, cx, cy);

   // Projection view
   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();

   // Set our current view perspective
   gluPerspective(35.0f, (float)cx / (float)cy, 0.1f, 2000.0f);

   // Model view
   glMatrixMode(GL_MODELVIEW);
}

void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
   int diffX = (int)(point.x - m_fLastX);
   int diffY = (int)(point.y - m_fLastY);
   m_fLastX  = (float)point.x;
   m_fLastY  = (float)point.y;

   // Left mouse button
   if (nFlags & MK_LBUTTON)
   {
      m_fRotX += (float)0.5f * diffY;
      if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f)) m_fRotX = 0.0f;

      m_fRotY += (float)0.5f * diffX;
      if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f)) m_fRotY = 0.0f;
   }

   // Right mouse button
   else if (nFlags & MK_RBUTTON)
   {
      m_fZoom -= (float)0.1f * diffY;
   }

   // Middle mouse button
   else if (nFlags & MK_MBUTTON)
   {
      m_fPosX += (float)0.05f * diffX;
      m_fPosY -= (float)0.05f * diffY;
   }

   if (nFlags)
   {
      OnDraw(NULL);
      oglDrawScene();
   }

   CWnd::OnMouseMove(nFlags, point);
}

void COpenGLControl::OnDraw(CDC *pDC)
{
	// TODO: Camera controls.
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
}
