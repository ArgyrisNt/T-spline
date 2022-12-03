#include "C:\Users\argir\T-spline\src\kVertex.cpp"
#include "C:\Users\argir\T-spline\src\tspline.cpp"
#include <iostream>
#include <fstream>

int main()
{
  bool paraview = false;
	kVertex vertices[25] = {kVertex(0.0,0.0),
             kVertex(0.2,0.0),
             kVertex(0.4,0.0),
             kVertex(0.6,0.0),
             kVertex(1.0,0.0),
             kVertex(0.2,0.2),
             kVertex(0.4,0.2),
             kVertex(0.6,0.2),
             kVertex(0.7,0.2),
             kVertex(1.0,0.2),
             kVertex(0.2,0.5),
             kVertex(0.4,0.5),
             kVertex(0.5,0.5),
             kVertex(0.7,0.5),
             kVertex(1.0,0.5),
             kVertex(0.0,0.65),
             kVertex(0.2,0.65),
             kVertex(0.5,0.7),
             kVertex(1.0,0.7),
             kVertex(0.2,0.8),
             kVertex(0.5,0.8),
             kVertex(0.0,1.0),
             kVertex(0.2,1.0),
             kVertex(0.5,1.0),
             kVertex(1.0,1.0)};

  int len = sizeof(vertices) / sizeof(*vertices);
  tspline t(len, 3);
  for (int i = 0; i < len; i++)
  {
    t.kVertices[i] = vertices[i];
  }

  for (int i = 0; i < len; i++)
  {
    t.kVertices[i].left_start = &t.kVertices[i];
    t.kVertices[i].right_start = &t.kVertices[i];
    t.kVertices[i].top_start = &t.kVertices[i];
    t.kVertices[i].bottom_start = &t.kVertices[i];
  }

	t.kVertices[0].right_end = &t.kVertices[1];
  t.kVertices[0].top_end = &t.kVertices[15];

  t.kVertices[1].top_end = &t.kVertices[5];
  t.kVertices[1].right_end = &t.kVertices[2];
  t.kVertices[1].left_end = &t.kVertices[0];

  t.kVertices[2].top_end = &t.kVertices[6];
  t.kVertices[2].right_end = &t.kVertices[3];
  t.kVertices[2].left_end = &t.kVertices[1];

  t.kVertices[3].top_end = &t.kVertices[7];
  t.kVertices[3].right_end = &t.kVertices[4];
  t.kVertices[3].left_end = &t.kVertices[2];

  t.kVertices[4].top_end = &t.kVertices[9];
  t.kVertices[4].left_end = &t.kVertices[3];

  t.kVertices[5].top_end = &t.kVertices[10];
  t.kVertices[5].right_end = &t.kVertices[6];
  t.kVertices[5].bottom_end = &t.kVertices[1];

  t.kVertices[6].top_end = &t.kVertices[11];
  t.kVertices[6].right_end = &t.kVertices[7];
  t.kVertices[6].bottom_end = &t.kVertices[2];
  t.kVertices[6].left_end = &t.kVertices[5];

  t.kVertices[7].right_end = &t.kVertices[8];
  t.kVertices[7].bottom_end = &t.kVertices[3];
  t.kVertices[7].left_end = &t.kVertices[6];

  t.kVertices[8].top_end = &t.kVertices[13];
  t.kVertices[8].right_end = &t.kVertices[9];
  t.kVertices[8].left_end = &t.kVertices[7];

  t.kVertices[9].top_end = &t.kVertices[14];
  t.kVertices[9].bottom_end = &t.kVertices[4];
  t.kVertices[9].left_end = &t.kVertices[8];

  t.kVertices[10].top_end = &t.kVertices[16];
  t.kVertices[10].right_end = &t.kVertices[11];
  t.kVertices[10].bottom_end = &t.kVertices[5];

  t.kVertices[11].right_end = &t.kVertices[12];
  t.kVertices[11].bottom_end = &t.kVertices[6];
  t.kVertices[11].left_end = &t.kVertices[10];

  t.kVertices[12].top_end = &t.kVertices[17];
  t.kVertices[12].right_end = &t.kVertices[13];
  t.kVertices[12].left_end = &t.kVertices[11];

  t.kVertices[13].right_end = &t.kVertices[14];
  t.kVertices[13].bottom_end = &t.kVertices[8];
  t.kVertices[13].left_end = &t.kVertices[12];

  t.kVertices[14].top_end = &t.kVertices[18];
  t.kVertices[14].bottom_end = &t.kVertices[9];
  t.kVertices[14].left_end = &t.kVertices[13];

  t.kVertices[15].top_end = &t.kVertices[21];
  t.kVertices[15].right_end = &t.kVertices[16];
  t.kVertices[15].bottom_end = &t.kVertices[0];

  t.kVertices[16].top_end = &t.kVertices[19];
  t.kVertices[16].bottom_end = &t.kVertices[10];
  t.kVertices[16].left_end = &t.kVertices[15];

  t.kVertices[17].top_end = &t.kVertices[20];
  t.kVertices[17].right_end = &t.kVertices[18];
  t.kVertices[17].bottom_end = &t.kVertices[12];

  t.kVertices[18].top_end = &t.kVertices[24];
  t.kVertices[18].bottom_end = &t.kVertices[14];
  t.kVertices[18].left_end = &t.kVertices[17];

  t.kVertices[19].top_end = &t.kVertices[22];
  t.kVertices[19].right_end = &t.kVertices[20];
  t.kVertices[19].bottom_end = &t.kVertices[16];

  t.kVertices[20].top_end = &t.kVertices[23];
  t.kVertices[20].bottom_end = &t.kVertices[17];
  t.kVertices[20].left_end = &t.kVertices[19];

  t.kVertices[21].right_end = &t.kVertices[22];
  t.kVertices[21].bottom_end = &t.kVertices[15];

  t.kVertices[22].right_end = &t.kVertices[23];
  t.kVertices[22].bottom_end = &t.kVertices[19];
  t.kVertices[22].left_end = &t.kVertices[21];

  t.kVertices[23].right_end = &t.kVertices[24];
  t.kVertices[23].bottom_end = &t.kVertices[20];
  t.kVertices[23].left_end = &t.kVertices[22];
 
  t.kVertices[24].bottom_end = &t.kVertices[18];
  t.kVertices[24].left_end = &t.kVertices[23];

  t.kVertices[0].cPoint = {0.0,0.0,1.0};
  t.kVertices[1].cPoint = {0.2,0.0,1.3};
  t.kVertices[2].cPoint = {0.4,0.0,1.6};
  t.kVertices[3].cPoint = {0.6,0.0,1.1};
  t.kVertices[4].cPoint = {1.0,0.0,1.0};
  t.kVertices[5].cPoint = {0.2,0.2,1.2};
  t.kVertices[6].cPoint = {0.4,0.2,1.2};
  t.kVertices[7].cPoint = {0.6,0.2,1.5};
  t.kVertices[8].cPoint = {0.7,0.2,1.1};
  t.kVertices[9].cPoint = {1.0,0.2,1.3};
  t.kVertices[10].cPoint = {0.2,0.5,1.2};
  t.kVertices[11].cPoint = {0.4,0.5,1.3};
  t.kVertices[12].cPoint = {0.5,0.5,1.5};
  t.kVertices[13].cPoint = {0.7,0.5,1.5};
  t.kVertices[14].cPoint = {1.0,0.5,1.1};
  t.kVertices[15].cPoint = {0.0,0.65,1.5};
  t.kVertices[16].cPoint = {0.2,0.65,1.5};
  t.kVertices[17].cPoint = {0.5,0.7,1.3};
  t.kVertices[18].cPoint = {1.0,0.7,1.1};
  t.kVertices[19].cPoint = {0.2,0.8,1.3};
  t.kVertices[20].cPoint = {0.5,0.8,1.1};
  t.kVertices[21].cPoint = {0.0,1.0,1.5};
  t.kVertices[22].cPoint = {0.2,1.0,1.6};
  t.kVertices[23].cPoint = {0.5,1.0,1.2};
  t.kVertices[24].cPoint = {1.0,1.0,1.1};

  t.updateKnotVecs();
  t.calc_faces();
  t.generate_extensions();
    
  //t.printControlPts(paraview);
  //t.printPreImagePaper(paraview);

  // std::string filename("T-surface.dat");
  // std::ofstream my_file(filename);

  // int count = 20;
  // my_file << "variables= " << "\"x\"" << "," << "\"y\"" << "," << "\"z\"" << "\n";
	// my_file << "zone t= " << "\"1\"" << ",i=" << count + 1 << ",j=" << count + 1 << "\n";

  // for (int i = 0; i <= count; i++)
  // {
  //   for (int j = 0; j <= count; j++)
  //   {
  //     std::vector<double> P = t.evaluate((1.0/count) * i, (1.0/count) * j);
	// 		my_file << P[0] << " " << P[1] << " " << P[2] << "\n";
  //   }
  // }
  // my_file.close();

  // if (paraview)
  // {
  //   plot(filename);
  // }

	return 0;
}