#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{

}


 void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //PointClould pc;
    //pc.loadPLY("./bun_zipper.ply");
    pc.loadPLYBinaryBigEndian("./xyzrgb_dragon.ply");

    AABB rootBox = AABB::computeBoundingBox(pc.points);

    octree = std::make_unique<Octree>(rootBox, 50, 6);
    for(auto &p : pc.points)
        octree->insert(p);

    shaderProgram = new QOpenGLShaderProgram;
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
    shaderProgram->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment.glsl");
    if(!shaderProgram->link())
    {
        qDebug()<<"shader program linked error";
        return;
    }
    VBO = std::make_unique<QOpenGLBuffer>(QOpenGLBuffer::VertexBuffer);
    VBO->create();
    VBO->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 *sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 *sizeof(GL_FLOAT), (void*)(3 *sizeof(GL_FLOAT)));


    VBO->allocate(pc.points.data(), pc.points.size() * sizeof(GL_FLOAT)*6);
}

void GLWidget::resizeGL(int w, int h)
{

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // std::vector<Point> visiblePoints;

    // octree->queryLOD(camera.position, 253.0f, visiblePoints);

    // std::vector<float> buffer;
    // for(auto &p : visiblePoints)
    // {
    //     buffer.push_back(p.position.x());
    //     buffer.push_back(p.position.y());
    //     buffer.push_back(p.position.z());
    //     buffer.push_back(p.color.x());
    //     buffer.push_back(p.color.y());
    //     buffer.push_back(p.color.z());
    // }

    shaderProgram->bind();
    shaderProgram->setUniformValue("MVP", camera.getMVP());

    VBO->bind();
    //VBO->allocate(buffer.data(), buffer.size() * sizeof(GL_FLOAT));


    glDrawArrays(GL_POINTS, 0, pc.points.size());
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint angleDelta = event->angleDelta();
    int verticalDelta = angleDelta.y();
    if (verticalDelta != 0) {
        float steps = verticalDelta / 120.0;  // 120 = 15 * 8
        camera.zoom(steps*0.1);
        update();
    }
}
