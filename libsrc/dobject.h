/*
	DOBJECT.CPP
	defines the class DObject

	Purpose: orderly class destruction, allows one object to
	destroy another one, especially when the object being
	destroyed has subparts that were dynamically allocated

	Copyright(c), All Rights Reserved, AHB: 30/04/95
*/
#if !defined (__DOBJECT_H)
#define __DOBJECT_H

class DObject {

public:

    virtual ~DObject();
    void static destroy( DObject * );
    virtual void end();

};

#endif // __DOBJECT_H
