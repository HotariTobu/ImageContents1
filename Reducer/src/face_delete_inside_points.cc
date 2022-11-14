// Created by yu-getu

#include "../include/face.h"

#include <vector>
#include <math.h>

void bubble_sort(std::vector<double> a, std::vector<int> b, int n);
int ccw(double x1, double y1, double x2, double y2, double x3, double y3);

void Face::DeleteInsidePoints() {

    std::vector<double> arg;
    std::vector<int> seq;
    std::vector<int> next;
    int head;
    int tail;
    int start;
    int points_size = _points.size();
    next.resize(points_size);

    for (int i = 0; i < _points.size(); i++){
        arg.push_back(atan2(_points[i].y,_points[i].x));
    }
    for (int i = 0; i < _points.size(); i++){
        seq.push_back(i);
    }

    bubble_sort(arg, seq, points_size);

    head = seq[0];
    int pnt = head;
    for (int i = 0; i < points_size; i++){
        next[seq[i]] = seq[i + 1];
    }
    tail = seq[points_size-1];
    next[tail] = head;

    start = 0;
    double tmp = _points[0].y;

    for (int i = 0; i < _points.size(); i++){

        if (tmp >= _points[i].y){
            tmp = _points[i].y;
            start = i;
        }
    }

    int a, b, c;
    int breakp = 1;

    while (breakp == 1){
        breakp = 0;
        a = start;
        b = next[a];
        c = next[b];
        while (1){
            if(ccw(_points[a].x,_points[a].y,_points[b].x,_points[a].y,_points[c].x, _points[c].y) == -1){
                breakp = 1;
                next[a] = next[next[a]];
                b = next[b];
                c = next[c];
            }
            else{
                a = next[a];
                b = next[b];
                c = next[c];
            }
            if (a == start){
                break;
            }
        }
    }

    std::vector<Point3d> new_points;
    pnt=start;

    while (1){
        new_points.push_back(_points[pnt]);
        pnt = next[pnt];
        if (pnt == start){
            break;
        }
    }

    _points.clear();
    _points = new_points;
}

void bubble_sort(std::vector<double> a, std::vector<int> b, int n){
    int i, j;
    double tmp = 0;
    for (i = 1; i <= n; i++){
        for (j = n - 1; j >= i; j--){
            if (a[j] < a[j - 1]){
                tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;

                tmp = b[j];
                b[j] = b[j - 1];
                b[j - 1] = tmp;
            }
        }
    }
}

int ccw(double x1, double y1, double x2, double y2, double x3, double y3){
    double dx1, dx2, dy1, dy2;
    dx1 = x2 - x1;
    dy1 = y2 - y1;
    dx2 = x3 - x1;
    dy2 = y3 - y1;
    if (dy1 * dx2 < dx1 * dy2){
        return 1;
    }
    else{
        return -1;
    }
}
