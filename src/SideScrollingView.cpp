/*
 * SideScrollingView.cpp
 *
 *  Created on: May 23, 2013
 *      Author: arjun
 */

#include "SideScrollingView.hpp"

static inline xy calculateViewport(const xy &pivotPosition, const xy &mapSize)
{
    xy v;

    if(mapSize.x > Sys()->getWindowProperties().size.x)
    {
        int x_central_first = Sys()->getWindowProperties().size.x/2;
        int x_central_last = mapSize.x - x_central_first;

        if(pivotPosition.x > x_central_last)
            v.x = mapSize.x - Sys()->getWindowProperties().size.x;
        else if(pivotPosition.x > x_central_first)
            v.x = pivotPosition.x - x_central_first;
    }

    if(mapSize.y > Sys()->getWindowProperties().size.y)
    {
        int y_central_first = Sys()->getWindowProperties().size.y/2;
        int y_central_last = mapSize.y - y_central_first;

        if(pivotPosition.y > y_central_last)
            v.y = mapSize.y - Sys()->getWindowProperties().size.y;
        else if(pivotPosition.y > y_central_first)
            v.y = pivotPosition.y - y_central_first;
    }

    return v;
}

void SideScrollingView::render()
{
    if(physicsMap != nullptr) {
        if(pivot == nullptr) {
            // Invoke drawAt() naively on each entity:
            for(auto e : physicsMap->entityMap.getEntities())
                e->d->drawAt(e->pos);
        }
        else {
            xy viewport = calculateViewport(
                    pivot->pos + pivot->d->getSize() / 2,
                    physicsMap->entityMap.getMapSize());

            // Invoke drawAt(pos - viewport) on each entity:
            for(auto e : physicsMap->entityMap.getEntities())
                e->d->drawAt(e->pos - viewport);
        }
    }
}