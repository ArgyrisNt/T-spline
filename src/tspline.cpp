#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "..\include\tspline.h"

void tspline::updateKnotVecs()
{
    for (int i = 0; i < len; i++) kVertices[i].updateKnotVec(deg);
}



std::vector<double> tspline::evaluateInRange(int resolution, bool plot)
{
    std::string filename("T-surface.dat");
    std::ofstream my_file(filename);
    if (plot)
    {
        my_file << "variables= " << "\"x\"" << "," << "\"y\"" << "," << "\"z\"" << "\n";
        my_file << "zone t= " << "\"1\"" << ",i=" << resolution + 1 << ",j=" << resolution + 1 << "\n";
    }

    std::vector<double> P(3, 0.0);
    for (int i = 0; i <= resolution; i++)
    {
        for (int j = 0; j <= resolution; j++)
        {
            P = evaluate((1.0 / resolution) * i, (1.0 / resolution) * j);
            if (plot) my_file << P[0] << " " << P[1] << " " << P[2] << "\n";
        }
    }

    if (plot) my_file.close();
}

std::vector<double> tspline::evaluate(double s, double t)
{
    std::vector<double> sumPB(3, 0.0);
    double sumB = 0.0;
    for (int i = 0; i < len; i++)
    {
        std::vector<double> knotVecS = kVertices[i].knotVec.first, knotVecT = kVertices[i].knotVec.second;
        bool is_s_insideKnotVecS = (s >= knotVecS[0]) && (s <= knotVecS.back());
        bool is_t_insideKnotVecT = (t >= knotVecT[0]) && (t <= knotVecT.back());
        if (is_s_insideKnotVecS && is_t_insideKnotVecT)
        {
            int knotspanS = 1, knotspanT = 1;

            double bs = basisFunTSpl(s, knotVecS, knotspanS);
            double bt = basisFunTSpl(t, knotVecT, knotspanT);

            sumPB[0] += kVertices[i].cPoint[0] * bs * bt;
            sumPB[1] += kVertices[i].cPoint[1] * bs * bt;
            sumPB[2] += kVertices[i].cPoint[2] * bs * bt;
            sumB += bs * bt;
        }
    }
    if (sumB < 1e-7) return sumPB;
    else
    {
        sumPB[0] /= sumB;
        sumPB[1] /= sumB;
        sumPB[2] /= sumB;
    }

    return sumPB;
}

double tspline::basisFunTSpl(double x, const std::vector<double>& knots, int knotspan)
{
    bool eq;
    if (fabs(x - knots[0]) < 1e-7)
    {
        eq = true;
        for (int i = 0; i < deg - 1; i++)
            if (knots[i] != knots[i+1]) eq = false;
        if (eq) return 1.0;
    }

    if (fabs(x - knots.back()) < 1e-7)
    {
        eq = true;
        for (int i = knots.size() - deg + 1; i < knots.size() - 1; i++)
            if (knots[i] != knots[i+1]) eq = false;
        if (eq) return 1.0;
    }

    return basisRecur(x, knots, deg, knotspan);
}

double basisRecur(double x, const std::vector<double>& knots, int deg, int knotspan)
{
    double N;
    if (deg == 0)
    {
        if ((x >= knots[knotspan]) && (x < knots[knotspan + 1])) N = 1.0;
        else N = 0.0;
    }
    else
    {
        double a = 0.0, b = 0.0;

        double ad = knots[knotspan + deg] - knots[knotspan];
        if (ad > 1e-7) a = ((x - knots[knotspan]) / ad) * basisRecur(x,knots,deg-1,knotspan);

        double bd = knots[knotspan + deg + 1] - knots[knotspan + 1];
        if (bd > 1e-7) b = ((knots[knotspan+deg+1] - x) / bd) * basisRecur(x, knots, deg-1, knotspan + 1);

        N = a + b;
    }

    return N;
}




void tspline::printControlPts()
{
    std::string filename("control_points.dat");
    std::ofstream my_file(filename);

    my_file << "variables= " << "\"x\"" << "," << "\"y\"" << "," << "\"z\"" <<"\n";
	my_file << "zone t= " << "\"1\"" << ",i=" << len << ",j=" << len << "\n";

    for (int i = 0; i < len; i++)
		my_file << kVertices[i].cPoint[0] << " " << kVertices[i].cPoint[1] << " " << kVertices[i].cPoint[2] << "\n";
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
        if (kVertices[i].top)
        {
            cnt += 2;
            my_file << "v " << kVertices[i].s << " " << kVertices[i].t << "\n";
            my_file << "v " << kVertices[i].top->end->s << " " << kVertices[i].top->end->t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }

        if (kVertices[i].right)
        {
            cnt += 2;
            my_file << "v " << kVertices[i].s << " " << kVertices[i].t << "\n";
            my_file << "v " << kVertices[i].right->end->s << " " << kVertices[i].right->end->t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }

        if (kVertices[i].bottom)
        {
            cnt += 2;
            my_file << "v " << kVertices[i].s << " " << kVertices[i].t << "\n";
            my_file << "v " << kVertices[i].bottom->end->s << " " << kVertices[i].bottom->end->t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }

        if (kVertices[i].left)
        {
            cnt += 2;
            my_file << "v " << kVertices[i].s << " " << kVertices[i].t << "\n";
            my_file << "v " << kVertices[i].left->end->s << " " << kVertices[i].left->end->t << "\n";
            my_file << "l " << cnt-1 << " " << cnt << "\n";
        }
    }
    my_file.close();
}

// bool tspline::is_bound(kVertex v)
// {
//     bool mode = false;
//     if ((v._s == kVertices[0]._s) || (v._s == kVertices[len-1]._s) || (v._t == kVertices[0]._t) || (v._t == kVertices[len-1]._t))
//     {
//         mode = true;
//     }

//     return mode;
// }

// X--<--<--X
// |        ^
// v        |
// X-->-->--X
// void tspline::calc_faces()
// {
//     for (int i = 0; i < len; i++)
//     {
//         if ((!kVertices[i].top_end) || (!kVertices[i].right_end))
//         {
//             continue;
//         }

//         // Start from bottom left corner
//         std::vector<double> coords;
//         coords.push_back(kVertices[i]._s);
//         coords.push_back(kVertices[i]._t);

//         // Find bottom right corner
//         kVertex next_vertex = *kVertices[i].right_end;
//         while (!next_vertex.top_end)
//         {
//             next_vertex = *next_vertex.right_end;
//         }
//         coords.push_back(next_vertex._s);
//         coords.push_back(next_vertex._t);

//         // Find top right corner
//         next_vertex = *next_vertex.top_end;
//         while (!next_vertex.left_end)
//         {
//             next_vertex = *next_vertex.top_end;
//         }
//         coords.push_back(next_vertex._s);
//         coords.push_back(next_vertex._t);

//         // Find top left corner
//         next_vertex = *next_vertex.left_end;
//         while (!next_vertex.bottom_end)
//         {
//             next_vertex = *next_vertex.left_end;
//         }
//         coords.push_back(next_vertex._s);
//         coords.push_back(next_vertex._t);

//         faces.push_back(coords);
//     }
// }

// void tspline::calc_Tjunctions()
// {
//     for (int i = 0; i < len; i++)
//     {
//         if ((!kVertices[i].top_end) || (!kVertices[i].right_end) || (!kVertices[i].bottom_end) || (!kVertices[i].left_end))
//         {
//             if (!is_bound(kVertices[i]))
//             {
//                 Tjunctions.push_back(i);
//             }
//         }
//     }
// }

// void tspline::generate_extensions()
// {
//     calc_Tjunctions();
//     kVertex temp[100] = {};
//     int count = 0;
//     for (int j = 0; j < Tjunctions.size(); j++)
//     {
//         int i = Tjunctions[j];
//         std::vector<double> vec1(kVertices[i].knotVec.first);
//         std::vector<double> vec2(kVertices[i].knotVec.second);
//         std::vector<double>::iterator ip1 = unique(vec1.begin(),vec1.begin()+vec1.size());
//         vec1.resize(std::distance(vec1.begin(), ip1));
//         std::vector<double>::iterator ip2 = unique(vec2.begin(),vec2.begin()+vec2.size());
//         vec2.resize(std::distance(vec2.begin(), ip2));

//         if (!kVertices[i].left_end)
//         {
//             auto coord = vec1.begin();
//             while (*coord < kVertices[i]._s)
//             {
//                 kVertex v_left(*coord,kVertices[i]._t);
//                 temp[count] = v_left;
//                 count++;
//                 coord = coord+1;
//             }
//         }
//         else if (!kVertices[i].bottom_end)
//         {
//             auto coord = vec2.begin();
//             while (*coord < kVertices[i]._t)
//             {
//                 kVertex v_bottom(kVertices[i]._s,*coord);
//                 temp[count] = v_bottom;
//                 count++;
//                 coord = coord+1;
//             }
//         }
//         else if (!kVertices[i].right_end)
//         {
//             auto coord = vec1.end()-1;
//             while (*coord > kVertices[i]._s)
//             {
//                 kVertex v_right(*coord,kVertices[i]._t);
//                 temp[count] = v_right;
//                 count++;
//                 coord = coord-1;
//             }
//         }
//         else if (!kVertices[i].top_end)
//         {
//             auto coord = vec2.end()-1;
//             while (*coord > kVertices[i]._t)
//             {
//                 kVertex v_top(kVertices[i]._s,*coord);
//                 temp[count] = v_top;
//                 count++;
//                 coord = coord-1;
//             }
//         }
//     }
//     f_len = count;
//     fVertices = new kVertex [f_len];
//     for (int i = 0; i < f_len; i++)
//     {
//         fVertices[i] = temp[i];
//     }
    
// }