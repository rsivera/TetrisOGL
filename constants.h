#pragma once

#include <vector>
#include <iostream>
#include <cassert>

#define PI 3.14159265f

typedef unsigned char uchar; // int between 0 and 255


const int NBTETRO=7;
// L Z S G T I O
const uchar COLOR[3*(NBTETRO+2)]=
  {
    0,0,0,
    255,255,255,
    200,125,0,
    12,100,200,
    65,32,123,
    200,0,200,
    150,150,150,
    0,200,20,
    200,150,20
  };

// Chaque forme est codée sur 16 bools, chaque rotation est une forme 
const bool VSHAPE[16*4*NBTETRO]=
  {
    // L (4)
    0,1,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,1,1,1,
    0,1,0,0,
    0,0,0,0,

    0,1,1,0,
    0,0,1,0,
    0,0,1,0,
    0,0,0,0,

    0,0,0,0,
    0,0,1,0,
    1,1,1,0,
    0,0,0,0,

    // Z (2)
    0,0,0,0,
    1,1,0,0,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,0,1,0,
    0,1,1,0,
    0,1,0,0,

    0,0,0,0,
    1,1,0,0,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,0,1,0,
    0,1,1,0,
    0,1,0,0,

    // S (2)
    0,0,0,0,
    0,0,1,1,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,1,0,

    0,0,0,0,
    0,0,1,1,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,1,0,

    // G (4)
    0,0,1,0,
    0,0,1,0,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,1,0,0,
    0,1,1,1,
    0,0,0,0,

    0,1,1,0, 
    0,1,0,0,
    0,1,0,0,
    0,0,0,0,

    0,0,0,0,
    1,1,1,0,
    0,0,1,0,
    0,0,0,0,

    // T (4)
    0,0,0,0,
    0,1,0,0,
    1,1,1,0,
    0,0,0,0,

    0,1,0,0,
    0,1,1,0,
    0,1,0,0,
    0,0,0,0,

    0,0,0,0,
    1,1,1,0,
    0,1,0,0,
    0,0,0,0,

    0,0,1,0,
    0,1,1,0,
    0,0,1,0,
    0,0,0,0,

    // I (2)
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,

    0,0,0,0,
    1,1,1,1,
    0,0,0,0,
    0,0,0,0,

    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,

    0,0,0,0,
    1,1,1,1,
    0,0,0,0,
    0,0,0,0,

    // O (1)
    0,0,0,0,
    0,1,1,0,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,1,1,0,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,1,1,0,
    0,1,1,0,
    0,0,0,0,

    0,0,0,0,
    0,1,1,0,
    0,1,1,0,
    0,0,0,0
  };

  