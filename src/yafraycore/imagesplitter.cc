/****************************************************************************
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <core_api/imagesplitter.h>
#include <iostream>

#include <algorithm>

__BEGIN_YAFRAY

// currently only supports creation of scanrow-ordered tiles
// shuffling would of course be easy, but i don't find that too usefull really,
// it does maximum damage to the coherency gain and visual feedback is medicore too

imageSpliter_t::imageSpliter_t(int w, int h, int x0,int y0, int bsize, tilesOrderType torder): blocksize(bsize), tilesorder(torder)
{
	int nx, ny;
	nx = (w+blocksize-1)/blocksize;
	ny = (h+blocksize-1)/blocksize;
	for(int j=0; j<ny; ++j)
	{
		for(int i=0; i<nx; ++i)
		{
			region_t r;
			r.x = x0 + i*blocksize;
			r.y = y0 + j*blocksize;
			r.w = std::min(blocksize, x0+w-r.x);
			r.h = std::min(blocksize, y0+h-r.y);
			regions.push_back(r);
		}
	}
	switch(tilesorder)
	{
		case RANDOM:	std::random_shuffle( regions.begin(), regions.end() );
		case LINEAR:
		default:	break;
	}
}

bool imageSpliter_t::getArea(int n, renderArea_t &area)
{
	if(n<0 || n>=(int)regions.size()) return false;
	region_t &r = regions[n];
	area.X = r.x;
	area.Y = r.y;
	area.W = r.w;
	area.H = r.h;
	return true;
}

__END_YAFRAY
