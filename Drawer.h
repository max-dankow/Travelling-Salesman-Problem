//
//  opengl.h
//  voyager
//
//  Created by Lokotochek on 19.05.15.
//  Copyright (c) 2015 Alexander Laktionov. All rights reserved.
//

#ifndef __voyager__opengl__
#define __voyager__opengl__
#include <vector>

void AnswerVisualizer(std::vector<std::pair<double, double>> &data, std::vector<std::pair<int, int>> &edges, int& DotsNum);
void SpanningTreeVisualizer(std::vector<std::pair<double, double>> &data, std::vector<std::vector<std::pair<int, int>>> &edges, int &DotsNum);


void reshape(int width, int height);

void display();
void display2();


void DrawPoints(float x1,float y1);



#endif /* defined(__voyager__opengl__) */
