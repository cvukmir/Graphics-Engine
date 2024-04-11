#pragma once

#ifndef ARCBOUNDARYCODES_HPP
#define ARCBOUNDARYCODES_HPP

#include "Arc3DPointH.h"
#include "ArcTypedefs.h"

struct ArcBoundaryCodes
{
public: // Constructor/Destructor(s) //

	ArcBoundaryCodes(const Arc3DPointH& point)
	{
		const double w  = point.w();
		values[0] = point.x();
		values[1] = w - values[0];
		values[2] = point.y();
		values[3] = w - values[2];
		values[4] = point.z();
		values[5] = w - values[4];

		if (values[0] < 0.0)
		{
			kode |= 0x00000001U;
		}

		if (values[1] < 0.0)
		{
			kode |= 0x00000002U;
		}

		if (values[2] < 0.0)
		{
			kode |= 0x00000004U;
		}

		if (values[3] < 0.0)
		{
			kode |= 0x00000008U;
		}

		if (values[4] < 0.0)
		{
			kode |= 0x00000010U;
		}

		if (values[5] < 0.0)
		{
			kode |= 0x00000020U;
		}
	}

	uint   kode = 0U;
	double values[6];


};

#endif // !ARCBOUNDARYCODES_HPP