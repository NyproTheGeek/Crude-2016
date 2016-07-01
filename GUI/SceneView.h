//17/06/16
#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QOpenGLWidget>

class SceneView : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit SceneView(QWidget *parent = 0);

signals:

public slots:
};

#endif // SCENEVIEW_H
