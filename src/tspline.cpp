#include <iostream>
#include <vector>
#include <fstream>
#include "C:\Users\argir\T-spline\include\tspline.h"

tspline::tspline() {}

tspline::tspline(int _len, int _deg)
{
    deg = _deg;
    len = _len;
    kVertices = new kVertex [_len];
}

void tspline::updateKnotVecs()
{
    for (int i = 0; i < len; i++)
    {
        kVertices[i].updateKnotVec(deg);
    }
}

std::vector<double> tspline::evaluate(double s, double t)
{
    std::vector<double> sumPB{0.0,0.0,0.0};
    double sumB = 0.0;
    for (int i = 0; i < len; i++)
    {
        if ((s >= kVertices[i].knotVec.first[0]) && (s <= kVertices[i].knotVec.first[kVertices[i].knotVec.first.size()-1]) && (t >= kVertices[i].knotVec.second[0]) && (t <= kVertices[i].knotVec.second[kVertices[i].knotVec.second.size()-1]))
        {
            int knotspanS = 1;
            int knotspanT = 1;

            double bs = 0.0;
            double bt = 0.0;

            bs = basisFunTSpl(s, kVertices[i].knotVec.first, deg, knotspanS);
            bt = basisFunTSpl(t, kVertices[i].knotVec.second, deg, knotspanT);
            
            double B = bs * bt;
            sumPB[0] = sumPB[0] + kVertices[i].cPoint[0]*B;
            sumPB[1] = sumPB[1] + kVertices[i].cPoint[1]*B;
            sumPB[2] = sumPB[2] + kVertices[i].cPoint[2]*B;
            sumB = sumB + B;
        }
    }
    std::vector<double> P{0.0,0.0,0.0};
    if (sumB < 1e-7)
    {
        P = sumPB;
    }
    else
    {
        P[0] = sumPB[0] / sumB;
        P[1] = sumPB[1] / sumB;
        P[2] = sumPB[2] / sumB;
    }

    return P;
}

void tspline::printControlPts()
{
    std::string filename("control_points.dat");
    std::ofstream my_file(filename);

    my_file << "variables= " << "\"x\"" << "," << "\"y\"" << "," << "\"z\"" <<"\n";
	my_file << "zone t= " << "\"1\"" << ",i=" << len << ",j=" << len << "\n";

    for (int i = 0; i < len; i++)
    {
		my_file << kVertices[i].cPoint[0] << " " << kVertices[i].cPoint[1] << " " << kVertices[i].cPoint[2] << "\n";
    }
    my_file.close();
}

void tspline::printPreImagePaper()
{
    std::string filename("pre_image.obj");
    std::ofstream my_file(filename);

    my_file << "# " << len << "\n";

    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        if (kVertices[i].top_end)
        {
            cnt += 2;
            my_file << "v " << kVertices[i]._s << " " << kVertices[i]._t << "\n";
            my_file << "v " << kVertices[i].top_end->_s << " " << kVertices[i].top_end->_t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }

        if (kVertices[i].right_end)
        {
            cnt += 2;
            my_file << "v " << kVertices[i]._s << " " << kVertices[i]._t << "\n";
            my_file << "v " << kVertices[i].right_end->_s << " " << kVertices[i].right_end->_t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }

        if (kVertices[i].bottom_end)
        {
            cnt += 2;
            my_file << "v " << kVertices[i]._s << " " << kVertices[i]._t << "\n";
            my_file << "v " << kVertices[i].bottom_end->_s << " " << kVertices[i].bottom_end->_t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }

        if (kVertices[i].left_end)
        {
            cnt += 2;
            my_file << "v " << kVertices[i]._s << " " << kVertices[i]._t << "\n";
            my_file << "v " << kVertices[i].left_end->_s << " " << kVertices[i].left_end->_t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }
    }
    my_file.close();
}