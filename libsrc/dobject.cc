/*
	DOBJECT.CPP
	defines the class DObject

	Purpose: orderly class destruction, allows one object to
	destroy another one, especially when the object being
	destroyed has subparts that were dynamically allocated

	Copyright(c), All Rights Reserved, AHB: 30/04/95
*/
#include "dobject.h"

DObject::~DObject()
{
}

void DObject::destroy( DObject * o )
{
    if( o != 0 )
        o->end();
    delete o;
}

void DObject::end() // should do object specific destruction
{

}
