#pragma once

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>

#include "data.h"
#include "graphics.h"
