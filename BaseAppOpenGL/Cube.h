#pragma once

#include <windows.h>	// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <glext.h>		// Header File For The Glext Library
#include <string>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#ifndef CUBE_H
#define CUBE_H

class Cube {
public:
    float x, y, z; // Posição do cubo
    float r, g, b; // Cor do cubo

    Cube(float x, float y, float z, float r, float g, float b) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->r = r;
        this->g = g;
        this->b = b;
    }

    // Função para desenhar o cubo
    float getHeight;
    void draw();
};

#endif
