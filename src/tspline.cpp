#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
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

void tspline::printControlPts(bool paraview)
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

    if (paraview)
    {
        plot(filename);
    }
}

void tspline::printPreImagePaper(bool paraview)
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

    if (paraview)
    {
        plot(filename);
    }
}

void tspline::print()
{
    for (int i = 0; i < len; i++)
    {
        kVertices[i].print();
    }
}

bool tspline::is_bound(kVertex v)
{
    bool mode = false;
    if ((v._s == kVertices[0]._s) || (v._s == kVertices[len-1]._s) || (v._t == kVertices[0]._t) || (v._t == kVertices[len-1]._t))
    {
        mode = true;
    }

    return mode;
}

// X--<--<--X
// |        ^
// v        |
// X-->-->--X
void tspline::calc_faces()
{
    for (int i = 0; i < len; i++)
    {
        if ((!kVertices[i].top_end) || (!kVertices[i].right_end))
        {
            continue;
        }

        // Start from bottom left corner
        std::vector<double> coords;
        coords.push_back(kVertices[i]._s);
        coords.push_back(kVertices[i]._t);

        // Find bottom right corner
        kVertex next_vertex = *kVertices[i].right_end;
        while (!next_vertex.top_end)
        {
            next_vertex = *next_vertex.right_end;
        }
        coords.push_back(next_vertex._s);
        coords.push_back(next_vertex._t);

        // Find top right corner
        next_vertex = *next_vertex.top_end;
        while (!next_vertex.left_end)
        {
            next_vertex = *next_vertex.top_end;
        }
        coords.push_back(next_vertex._s);
        coords.push_back(next_vertex._t);

        // Find top left corner
        next_vertex = *next_vertex.left_end;
        while (!next_vertex.bottom_end)
        {
            next_vertex = *next_vertex.left_end;
        }
        coords.push_back(next_vertex._s);
        coords.push_back(next_vertex._t);

        faces.push_back(coords);
    }
}

void tspline::calc_Tjunctions()
{
    for (int i = 0; i < len; i++)
    {
        if ((!kVertices[i].top_end) || (!kVertices[i].right_end) || (!kVertices[i].bottom_end) || (!kVertices[i].left_end))
        {
            if (!is_bound(kVertices[i]))
            {
                Tjunctions.push_back(i);
            }
        }
    }
}

void tspline::generate_extensions()
{
    calc_Tjunctions();
    kVertex temp[100] = {};
    int count = 0;
    for (int j = 0; j < Tjunctions.size(); j++)
    {
        int i = Tjunctions[j];
        std::vector<double> vec1(kVertices[i].knotVec.first);
        std::vector<double> vec2(kVertices[i].knotVec.second);
        std::vector<double>::iterator ip1 = unique(vec1.begin(),vec1.begin()+vec1.size());
        vec1.resize(std::distance(vec1.begin(), ip1));
        std::vector<double>::iterator ip2 = unique(vec2.begin(),vec2.begin()+vec2.size());
        vec2.resize(std::distance(vec2.begin(), ip2));

        if (!kVertices[i].left_end)
        {
            auto coord = vec1.begin();
            while (*coord < kVertices[i]._s)
            {
                kVertex v_left(*coord,kVertices[i]._t);
                temp[count] = v_left;
                count++;
                coord = coord+1;
            }
        }
        else if (!kVertices[i].bottom_end)
        {
            auto coord = vec2.begin();
            while (*coord < kVertices[i]._t)
            {
                kVertex v_bottom(kVertices[i]._s,*coord);
                temp[count] = v_bottom;
                count++;
                coord = coord+1;
            }
        }
        else if (!kVertices[i].right_end)
        {
            auto coord = vec1.end()-1;
            while (*coord > kVertices[i]._s)
            {
                kVertex v_right(*coord,kVertices[i]._t);
                temp[count] = v_right;
                count++;
                coord = coord-1;
            }
        }
        else if (!kVertices[i].top_end)
        {
            auto coord = vec2.end()-1;
            while (*coord > kVertices[i]._t)
            {
                kVertex v_top(kVertices[i]._s,*coord);
                temp[count] = v_top;
                count++;
                coord = coord-1;
            }
        }
    }
    f_len = count;
    fVertices = new kVertex [f_len];
    for (int i = 0; i < f_len; i++)
    {
        fVertices[i] = temp[i];
    }
    
}