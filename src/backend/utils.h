#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 1e-6

/**
 * @brief 
 * 
 * @param maxFacetsSize 
 * @param countOfVertexes 
 * @param countOfFacets 
 * @param vert_in_polygons 
 * @param vertexes
 * @param vertexes
 * 
 */
typedef struct data {
    int maxFacetsSize;
    int countOfVertexes;
    int countOfFacets;
    int vert_in_polygons;
    double* vertexes;
    int* facets;
} data_t;

/**
 * @brief parser for read NUMBER OF VERTEXES and FACETS
 * 
 * @param pathFile 
 * @return data_t structure include NUMBER OF VERTEXES and FACETS
 */
data_t readCount(const char *pathFile);

/**
 * @brief parser for read vertexes coordinate and vertex numbers in facetes
 * 
 * @param pathFile 
 * @param newData structure data_t
 */

void readData(const char *pathFile, data_t *newData);

/**
 * @brief provide number of vertex 
 * provide number of vertex and transfom from str to int
 * "43/33/85" -> 43
 * @param input string with (number of vertex)/(values of texture coordinates)/(normal values)
 * @return int number of vertex
 */
int facetProcessing(char *input);

double degree_to_rad(double angle);

/**
 * @brief Move model along the X axis
 * 
 * @param A coordinate matrix
 * @param x moving along the X axis
 */
void move_x(data_t *A, double x);

/**
 * @brief Move model along the Y axis
 * 
 * @param A coordinate matrix
 * @param y moving along the Y axis
 */
void move_y(data_t *A, double y);

/**
 * @brief Move model along the Z axis
 * 
 * @param A coordinate matrix
 * @param z moving along the Z axis
 */
void move_z(data_t *A, double z);

/**
 * @brief Change the rotation angle relative to the X axes
 * 
 * @param A coordinate matrix
 * @param angle rotation angle relative to the X axes
 */
void rotation_by_ox(data_t *A, double angle);

/**
 * @brief Change the rotation angle relative to the Y axes
 * 
 * @param A coordinate matrix
 * @param angle rotation angle relative to the Y axes
 */
void rotation_by_oy(data_t *A, double angle);

/**
 * @brief Change the rotation angle relative to the Z axes
 * 
 * @param A coordinate matrix
 * @param angle rotation angle relative to the Z axes
 */
void rotation_by_oz(data_t *A, double angle);

/**
 * @brief Change the scale of model
 * 
 * @param A coordinate matrix
 * @param scale ratio of scale
 */
void scale(data_t *A, double scale);

#endif // SRC_BACKEND_UTILS_H_