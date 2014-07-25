#ifndef ContactListener_h__
#define ContactListener_h__

#include "cocos2d.h"
#include "Box2d/Box2d.h"

class ContactListener : public b2ContactListener
{
private:
	virtual void  BeginContact(b2Contact*contact);
	virtual void  EndContact(b2Contact*contact);
	virtual void  PreSolve(b2Contact*contact ,const b2Manifold* oldmanifold);
	virtual void  PostSolve(b2Contact*contact,const b2ContactImpulse*impulse);
};
#endif // ContactListener_h__
