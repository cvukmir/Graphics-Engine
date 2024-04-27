#pragma once

#ifndef ARCTYPEDEFS_H
#define ARCTYPEDEFS_H

// Stdlib
#include <vector>
#include <stack>
#include <list>

#include "ArcBaseTypes.h"
#include "ArcTransformMatrixH.h"
#include "Arc3DAttributedPoint.h"
#include "ArcFarLight.hpp"
#include "ArcPointLight.hpp"

typedef std::stack<ArcTransformMatrixH*>   ArcTransformationStack;
typedef std::list<uint*>                   ArcFrameList;
typedef std::vector<Arc3DAttributedPoint*> Arc3DAttributedPointList;
typedef std::vector<ArcFarLight*>          ArcFarLightList;
typedef std::vector<ArcPointLight*>        ArcPointLightList;

#endif // !ARCTYPEDEFS_H
