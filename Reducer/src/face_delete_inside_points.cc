// Created by guinpen98

#include "../include/face.h"

#include <vector>
#include <cmath>
#include <algorithm>

bool ccw(const double x1, const double y1, const double x2, const double y2, const double x3, const double y3){
    double dx1 = x2 - x1;
    double dy1 = y2 - y1;
    double dx2 = x3 - x1;
    double dy2 = y3 - y1;
    return dy1 * dx2 < dx1 * dy2;
}

void Face::DeleteInsidePoints() {
    std::vector<std::pair<double, int>> arg_seq;
    int points_size = (int)_points.size();
    for (int i = 0; i < points_size; ++i){
        arg_seq.push_back({std::atan2(_points[i].y,_points[i].x), i});
    }

    std::sort(arg_seq.begin(), arg_seq.end(), [](const std::pair<double, int>& as1, const std::pair<double, int>& as2){return as1.first < as2.first;});
    
    const int head = arg_seq[0].second;
    int pnt = head;
    int start = head;

    std::vector<int> next_num(points_size);
    for (int i = 0; i < points_size - 1; ++i){
        next_num[pnt] = arg_seq[i + 1].second;
        pnt = next_num[pnt];
    }
    next_num[arg_seq[points_size - 1].second] = head;

    double min = _points[head].y;
    for (int i = 0; i < points_size; ++i){
        if(_points[arg_seq[pnt].second].y < min){
            start=pnt;
            min = _points[arg_seq[pnt].second].y;
        }
        pnt = next_num[pnt];
    }

    pnt=start;
    int tmp_cnt = 0;
    int cnt = 0;
    int next1;
    int next2;
    while(1){
        tmp_cnt = cnt;
        while(1){
            next1 = next_num[pnt];
            next2 = next_num[next1];
            if(!ccw(_points[pnt].x,_points[pnt].y, _points[next1].x, _points[next1].y, _points[next2].x, _points[next2].y)){
                next_num[pnt] = next_num[next1];
                cnt++;
            } else{
                pnt = next1;
            }
            if(pnt == start){
                break;
            }
        }
        if(tmp_cnt == cnt){
            break;
        }
    }

    std::vector<Point3d> new_points;
    pnt = start;

    while (1){
        new_points.push_back(_points[pnt]);
        pnt = next_num[pnt];
        if (pnt == start){
            break;
        }
    }

    _points.clear();
    _points = new_points;
}


