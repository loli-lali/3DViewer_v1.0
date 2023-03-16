#include "utils.h"

// int main(void) {
//     // data_t *newData = NULL;
//     data_t A = readCount("../models/pyramid.obj");
//     //printf("111\n");
//     readData("../models/pyramid.obj", &A);
//     printf("num of vertexes = %d\nnum of facets = %d\nsum of vertexes in all
//     facets = %d\nmax facets size = %d\n",
//             A.countOfVertexes, A.countOfFacets, A.vert_in_polygons,
//             A.maxFacetsSize);
//     printf("Координаты вершин\n");
//     for (int i = 0; i < A.countOfVertexes * 3 + 3; i++) {
//         printf("%lf ", A.vertexes[i]);
//     }
//     printf("\n");
//     printf("Грани\n");
//     for (int i = 0; i < A.vert_in_polygons*2; i++) {
//         printf("%d ", A.facets[i]);
//     }
//     return 0;
// }

data_t readCount(const char *pathFile) {
  data_t newData = {0};
  FILE *opFile;
  opFile = fopen(pathFile, "r");
  if (opFile) {
    size_t lan = 0;
    ssize_t strLen;
    char *dataStr = calloc(512, sizeof(char));
    char sep[10] = " ";
    int countVertInFacets = 0;
    while ((strLen = getline(&dataStr, &lan, opFile)) > 0) {
      if (dataStr[0] == 'v' && dataStr[1] == ' ') {
        newData.countOfVertexes++;
        continue;
      } else if (dataStr[0] == 'f' && dataStr[1] == ' ') {
        newData.countOfFacets++;
        char *tokStr = strtok(dataStr, sep);
        while (tokStr != NULL) {
          tokStr = strtok(NULL, sep);
          // считаем количество вершин для каждой грани
          if (tokStr != NULL) {
            newData.vert_in_polygons++;
            countVertInFacets++;
          }
        }
        if (countVertInFacets > newData.maxFacetsSize) {
          newData.maxFacetsSize = countVertInFacets;
        }
        countVertInFacets = 0;
        continue;
      }
    }
    free(dataStr);
    fclose(opFile);
  }
  return newData;
}

void readData(const char *pathFile, data_t *newData) {
  FILE *opFile;
  opFile = fopen(pathFile, "r");
  if (opFile) {
    //
    newData->vertexes =
        malloc((newData->countOfVertexes * 3 + 3) * sizeof(double));
    newData->facets = malloc(newData->vert_in_polygons * 2 * sizeof(double));
    int *tempFacets = malloc(newData->maxFacetsSize * sizeof(int));

    char *dataStr = calloc(1024, sizeof(char));
    size_t lan = 0;
    ssize_t strLen;
    char sep[2] = " ";
    int vert_i = 0;
    // counter vertexes in newData.facets
    int countVertInFacet = 0;
    for (int i = 0; i < 3; i++) {
      newData->vertexes[i] = 0;
      vert_i++;
    }
    while ((strLen = getline(&dataStr, &lan, opFile)) > 0) {
      if (dataStr[0] == 'v' && dataStr[1] == ' ') {
        char *tokStr = strtok(dataStr, sep);
        int digits_in_line = 0;
        double tempCoordinate;
        while (tokStr != NULL && digits_in_line < 4) {
          tokStr = strtok(NULL, sep);
          if (tokStr != NULL) {
            tempCoordinate = strtod(tokStr, NULL);
            newData->vertexes[vert_i] = tempCoordinate;
            vert_i++;
          }
          digits_in_line++;
        }
      } else if (dataStr[0] == 'f' && dataStr[1] == ' ') {
        char *tokStr = strtok(dataStr, sep);
        // число вершин у одной грани
        int tempVertNumb = 1;
        while (tokStr != NULL) {
          tokStr = strtok(NULL, sep);
          // write vertexes of one facet in array
          if (tokStr != NULL) {
            tempFacets[tempVertNumb - 1] = facetProcessing(tokStr);
            tempVertNumb++;
          }
        }
        tempVertNumb--;
        // i хранит в себе количество вершин в последней грани
        newData->facets[countVertInFacet] = tempFacets[0];
        newData->facets[countVertInFacet + 2 * tempVertNumb - 1] =
            tempFacets[0];
        for (int i = 1; i < tempVertNumb; i++) {
          newData->facets[countVertInFacet + 2 * i - 1] = tempFacets[i];
          newData->facets[countVertInFacet + 2 * i] = tempFacets[i];
        }
        countVertInFacet += tempVertNumb * 2;
      }
    }
    free(tempFacets);
    free(dataStr);
    fclose(opFile);
  }
}

int facetProcessing(char *input) {
  char *sepVert = "/";
  char tempStrVert[64] = {0};
  int vertNum;

  size_t vertNumbSize = strcspn(input, sepVert);
  strncpy(tempStrVert, input, vertNumbSize);
  vertNum = atoi(tempStrVert);

  return vertNum;
}
