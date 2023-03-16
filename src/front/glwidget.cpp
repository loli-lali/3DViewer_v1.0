#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  back_color.setRgb(0, 0, 0, 255);
  edge_color.setRgb(255, 255, 255, 255);
  vert_color.setRgb(255, 255, 255, 255);
}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::paintGL() {
  // update();
  // вид проекции
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->proection_type == 0) {
    glOrtho(-1, 1, -1, 1, 1, 20);
  } else {
    glFrustum(-1, 1, -1, 1, 1, 20);
  }
  glTranslatef(0, 0, -7);

  // задать цвет фона
  glClearColor(back_color.redF(), back_color.greenF(), back_color.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // толщина линий, размер точек
  glPointSize(vert_size);
  glLineWidth(edge_thickness);

  if (this->edge_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
  } else if (this->edge_type == 0) {
    glDisable(GL_LINE_STIPPLE);
  }

  if (this->file_added == 1) {
    scale(this->res, (this->scale_obj / this->scale_obj_prev));
    move_x(this->res, (this->X_move - this->X_move_prev));
    move_y(this->res, (this->Y_move - this->Y_move_prev));
    move_z(this->res, (this->Z_move - this->Z_move_prev));
    rotation_by_ox(this->res, (this->X_rotate - this->X_rotate_prev));
    rotation_by_oy(this->res, (this->Y_rotate - this->Y_rotate_prev));
    rotation_by_oz(this->res, (this->Z_rotate - this->Z_rotate_prev));

    glVertexPointer(3, GL_DOUBLE, 0, this->res->vertexes);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(edge_color.redF(), edge_color.greenF(), edge_color.blueF());
    glDrawElements(GL_LINES, this->res->vert_in_polygons * 2, GL_UNSIGNED_INT,
                   this->res->facets);
    glDisableClientState(GL_VERTEX_ARRAY);

    if (this->vert_type != 0) {
      if (this->vert_type == 1) {
        glEnable(GL_POINT_SMOOTH);
      } else {
        glDisable(GL_POINT_SMOOTH);
      }
      glEnableClientState(GL_VERTEX_ARRAY);
      glColor3d(vert_color.redF(), vert_color.greenF(), vert_color.blueF());
      glDrawArrays(GL_POINTS, 3, this->res->countOfVertexes);
      glDisableClientState(GL_VERTEX_ARRAY);
    }
  }
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
