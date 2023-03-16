#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QObject>

extern "C" {
#include "../backend/utils.h"
}

class GLWidget : public QOpenGLWidget
{
public:
    explicit GLWidget(QWidget *parent = 0);
    // GLWidget();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    int file_added = 0;
    data_t *res;
    QString filename = "\0";

    double X_move = 0;
    double X_move_prev = 0;
    double Y_move = 0;
    double Y_move_prev = 0;
    double Z_move = 0;
    double Z_move_prev = 0;

    double X_rotate = 0;
    double X_rotate_prev = 0;
    double Y_rotate = 0;
    double Y_rotate_prev = 0;
    double Z_rotate = 0;
    double Z_rotate_prev = 0;

    double scale_obj = 1;
    double scale_obj_prev = 1;

    int proection_type = 0;
    QColor back_color;

    int edge_type = 0;
    QColor edge_color;
    int edge_thickness = 1;

    int vert_type = 0;
    QColor vert_color;
    int vert_size = 1;

};

#endif // GLWIDGET_H
