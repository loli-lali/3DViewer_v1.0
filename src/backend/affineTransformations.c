#include "utils.h"

void move_x(data_t *A, double x) {
  for (int i = 0; i <= A->countOfVertexes * 3 + 3; i = i + 3) {
    A->vertexes[i] += x;
  }
}

void move_y(data_t *A, double y) {
  for (int i = 0; i <= A->countOfVertexes * 3 + 3; i = i + 3) {
    A->vertexes[i + 1] += y;
  }
}

void move_z(data_t *A, double z) {
  for (int i = 0; i <= A->countOfVertexes * 3 + 3; i = i + 3) {
    A->vertexes[i + 2] += z;
  }
}

double degree_to_rad(double angle) {
  angle = angle * M_PI / 180;
  return angle;
}

void rotation_by_ox(data_t *A, double angle) {
  for (int i = 1; i <= A->countOfVertexes * 3 + 3; i += 3) {
    double temp_y = A->vertexes[i];
    double temp_z = A->vertexes[i + 1];
    A->vertexes[i] = cos(angle) * temp_y + sin(angle) * temp_z;
    A->vertexes[i + 1] = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotation_by_oy(data_t *A, double angle) {
  for (int i = 0; i <= A->countOfVertexes * 3 + 3; i += 3) {
    double temp_x = A->vertexes[i];
    double temp_z = A->vertexes[i + 2];
    A->vertexes[i] = cos(angle) * temp_x - sin(angle) * temp_z;
    A->vertexes[i + 2] = sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void rotation_by_oz(data_t *A, double angle) {
  for (int i = 0; i <= A->countOfVertexes * 3 + 3; i += 3) {
    double temp_x = A->vertexes[i];
    double temp_y = A->vertexes[i + 1];
    A->vertexes[i] = cos(angle) * temp_x + sin(angle) * temp_y;
    A->vertexes[i + 1] = -sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void scale(data_t *A, double scale) {
  for (int i = 0; i < A->countOfVertexes * 3 + 3; i++) {
    A->vertexes[i] *= scale;
  }
}
