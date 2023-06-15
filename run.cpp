#include "C:\Users\argir\T-spline\include\kVertex.h"
#include "C:\Users\argir\T-spline\src\tspline.cpp"
#include <iostream>
#include <fstream>

int main()
{
  std::vector<kVertex> vertices = {kVertex(0.0,0.0), kVertex(0.2,0.0), kVertex(0.4,0.0), kVertex(0.6,0.0), kVertex(1.0,0.0), kVertex(0.2,0.2), kVertex(0.4,0.2),
                                   kVertex(0.6,0.2), kVertex(0.7,0.2), kVertex(1.0,0.2), kVertex(0.2,0.5), kVertex(0.4,0.5), kVertex(0.5,0.5), kVertex(0.7,0.5),
                                   kVertex(1.0,0.5), kVertex(0.0,0.65), kVertex(0.2,0.65), kVertex(0.5,0.7), kVertex(1.0,0.7), kVertex(0.2,0.8), kVertex(0.5,0.8),
                                   kVertex(0.0,1.0), kVertex(0.2,1.0), kVertex(0.5,1.0), kVertex(1.0,1.0)};

  tspline t(3, vertices);
  t.kVertices = vertices;

  {
    t.kVertices[0].cnctRight(t.kVertices[1]);
    t.kVertices[0].cnctTop(t.kVertices[15]);

    t.kVertices[1].cnctTop(t.kVertices[5]);
    t.kVertices[1].cnctRight(t.kVertices[2]);
    t.kVertices[1].cnctLeft(t.kVertices[0]);

    t.kVertices[2].cnctTop(t.kVertices[6]);
    t.kVertices[2].cnctRight(t.kVertices[3]);
    t.kVertices[2].cnctLeft(t.kVertices[1]);

    t.kVertices[3].cnctTop(t.kVertices[7]);
    t.kVertices[3].cnctRight(t.kVertices[4]);
    t.kVertices[3].cnctLeft(t.kVertices[2]);

    t.kVertices[4].cnctTop(t.kVertices[9]);
    t.kVertices[4].cnctLeft(t.kVertices[3]);

    t.kVertices[5].cnctTop(t.kVertices[10]);
    t.kVertices[5].cnctRight(t.kVertices[6]);
    t.kVertices[5].cnctBottom(t.kVertices[1]);

    t.kVertices[6].cnctTop(t.kVertices[11]);
    t.kVertices[6].cnctRight(t.kVertices[7]);
    t.kVertices[6].cnctBottom(t.kVertices[2]);
    t.kVertices[6].cnctLeft(t.kVertices[5]);

    t.kVertices[7].cnctRight(t.kVertices[8]);
    t.kVertices[7].cnctBottom(t.kVertices[3]);
    t.kVertices[7].cnctLeft(t.kVertices[6]);

    t.kVertices[8].cnctTop(t.kVertices[13]);
    t.kVertices[8].cnctRight(t.kVertices[9]);
    t.kVertices[8].cnctLeft(t.kVertices[7]);

    t.kVertices[9].cnctTop(t.kVertices[14]);
    t.kVertices[9].cnctBottom(t.kVertices[4]);
    t.kVertices[9].cnctLeft(t.kVertices[8]);

    t.kVertices[10].cnctTop(t.kVertices[16]);
    t.kVertices[10].cnctRight(t.kVertices[11]);
    t.kVertices[10].cnctBottom(t.kVertices[5]);

    t.kVertices[11].cnctRight(t.kVertices[12]);
    t.kVertices[11].cnctBottom(t.kVertices[6]);
    t.kVertices[11].cnctLeft(t.kVertices[10]);

    t.kVertices[12].cnctTop(t.kVertices[17]);
    t.kVertices[12].cnctRight(t.kVertices[13]);
    t.kVertices[12].cnctLeft(t.kVertices[11]);

    t.kVertices[13].cnctRight(t.kVertices[14]);
    t.kVertices[13].cnctBottom(t.kVertices[8]);
    t.kVertices[13].cnctLeft(t.kVertices[12]);

    t.kVertices[14].cnctTop(t.kVertices[18]);
    t.kVertices[14].cnctBottom(t.kVertices[9]);
    t.kVertices[14].cnctLeft(t.kVertices[13]);

    t.kVertices[15].cnctTop(t.kVertices[21]);
    t.kVertices[15].cnctRight(t.kVertices[16]);
    t.kVertices[15].cnctBottom(t.kVertices[0]);

    t.kVertices[16].cnctTop(t.kVertices[19]);
    t.kVertices[16].cnctBottom(t.kVertices[10]);
    t.kVertices[16].cnctLeft(t.kVertices[15]);

    t.kVertices[17].cnctTop(t.kVertices[20]);
    t.kVertices[17].cnctRight(t.kVertices[18]);
    t.kVertices[17].cnctBottom(t.kVertices[12]);

    t.kVertices[18].cnctTop(t.kVertices[24]);
    t.kVertices[18].cnctBottom(t.kVertices[14]);
    t.kVertices[18].cnctLeft(t.kVertices[17]);

    t.kVertices[19].cnctTop(t.kVertices[22]);
    t.kVertices[19].cnctRight(t.kVertices[20]);
    t.kVertices[19].cnctBottom(t.kVertices[16]);

    t.kVertices[20].cnctTop(t.kVertices[23]);
    t.kVertices[20].cnctBottom(t.kVertices[17]);
    t.kVertices[20].cnctLeft(t.kVertices[19]);

    t.kVertices[21].cnctRight(t.kVertices[22]);
    t.kVertices[21].cnctBottom(t.kVertices[15]);

    t.kVertices[22].cnctRight(t.kVertices[23]);
    t.kVertices[22].cnctBottom(t.kVertices[19]);
    t.kVertices[22].cnctLeft(t.kVertices[21]);

    t.kVertices[23].cnctRight(t.kVertices[24]);
    t.kVertices[23].cnctBottom(t.kVertices[20]);
    t.kVertices[23].cnctLeft(t.kVertices[22]);

    t.kVertices[24].cnctBottom(t.kVertices[18]);
    t.kVertices[24].cnctLeft(t.kVertices[23]);
  }

  {
    t.kVertices[0].cPoint = {0.0, 0.0, 1.0};
    t.kVertices[1].cPoint = {0.2, 0.0, 1.3};
    t.kVertices[2].cPoint = {0.4, 0.0, 1.6};
    t.kVertices[3].cPoint = {0.6, 0.0, 1.1};
    t.kVertices[4].cPoint = {1.0, 0.0, 1.0};
    t.kVertices[5].cPoint = {0.2, 0.2, 1.2};
    t.kVertices[6].cPoint = {0.4, 0.2, 1.2};
    t.kVertices[7].cPoint = {0.6, 0.2, 1.5};
    t.kVertices[8].cPoint = {0.7, 0.2, 1.1};
    t.kVertices[9].cPoint = {1.0, 0.2, 1.3};
    t.kVertices[10].cPoint = {0.2, 0.5, 1.2};
    t.kVertices[11].cPoint = {0.4, 0.5, 1.3};
    t.kVertices[12].cPoint = {0.5, 0.5, 1.5};
    t.kVertices[13].cPoint = {0.7, 0.5, 1.5};
    t.kVertices[14].cPoint = {1.0, 0.5, 1.1};
    t.kVertices[15].cPoint = {0.0, 0.65, 1.5};
    t.kVertices[16].cPoint = {0.2, 0.65, 1.5};
    t.kVertices[17].cPoint = {0.5, 0.7, 1.3};
    t.kVertices[18].cPoint = {1.0, 0.7, 1.1};
    t.kVertices[19].cPoint = {0.2, 0.8, 1.3};
    t.kVertices[20].cPoint = {0.5, 0.8, 1.1};
    t.kVertices[21].cPoint = {0.0, 1.0, 1.5};
    t.kVertices[22].cPoint = {0.2, 1.0, 1.6};
    t.kVertices[23].cPoint = {0.5, 1.0, 1.2};
    t.kVertices[24].cPoint = {1.0, 1.0, 1.1};
  }

  t.printPreImagePaper();
  t.printControlPts();
  t.updateKnotVecs();

  int resolution = 20;
  bool plot = true;
  t.evaluateInRange(resolution, plot);

  // t.calc_faces();
  // t.generate_extensions();

	return 0;
}