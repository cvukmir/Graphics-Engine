#pragma once

#ifndef ARCTYPEDEFS_H
#define ARCTYPEDEFS_H

// Stdlib
#include <vector>
#include <stack>
#include <list>

// ArcGraphicsEngine
#include "ArcTransformMatrixH.h"

typedef unsigned int uint;
typedef std::stack<ArcTransformMatrixH*> ArcTransformationStack;
typedef std::list<uint*>                 ArcFrameList;

#endif // !ARCTYPEDEFS_H
