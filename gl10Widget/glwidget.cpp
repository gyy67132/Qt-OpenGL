#include "glwidget.h"

GLWidget::GLWidget()
{
    QSurfaceFormat format;
    format.setVersion(1, 1);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    setFormat(format);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslated(0, 0, -10);
    glScaled(m_scale, m_scale, m_scale);

    glRotated(m_xRot, 1, 0, 0);
    glRotated(m_yRot, 0, 1, 0);
    glRotated(m_zRot, 0, 0, 1);

    glCallList(m_object);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    m_object = makeObject();
    glShadeModel(GL_FLAT);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)(w), (GLint)(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 5, 15);
    glMatrixMode(GL_MODELVIEW);
}

GLuint GLWidget::makeObject()
{
    GLuint list;
    list = glGenLists(1);

    glNewList(list, GL_COMPILE);

    glColor3d(1, 1, 1);

    glLineWidth(2);

    glBegin(GL_LINE_LOOP);
    glVertex3d(1, 0.5, -0.4);
    glVertex3d(1, -0.5, -0.4);
    glVertex3d(-1, -0.5, -0.4);
    glVertex3d(-1, 0.5, -0.4);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3d(1, 0.5, 0.4);
    glVertex3d(1, -0.5, 0.4);
    glVertex3d(-1, -0.5, 0.4);
    glVertex3d(-1, 0.5, 0.4);
    glEnd();

    glBegin(GL_LINES);
    glVertex3d(1, 0.5, -0.4);  glVertex3d(1, 0.5, 0.4);
    glVertex3d(1, -0.5, -0.4); glVertex3d(1, -0.5, 0.4);
    glVertex3d(-1, -0.5, -0.4); glVertex3d(-1, -0.5, 0.4);
    glVertex3d(-1, 0.5, -0.4); glVertex3d(-1, 0.5, 0.4);
    glEnd();

    glEndList();

    return list;
}
