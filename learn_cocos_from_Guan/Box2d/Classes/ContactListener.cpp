#include "ContactListener.h"

USING_NS_CC;
void  ContactListener::BeginContact(b2Contact*contact)
{
	log("BeginContact");
	b2Body* bodyA=contact->GetFixtureA()->GetBody();
	b2Body* bodyB=contact->GetFixtureB()->GetBody();
	auto SpA = (Sprite*)bodyA->GetUserData();
	auto SpB = (Sprite*)bodyB->GetUserData();
	if(SpA != nullptr && SpB!=nullptr)
	{
		SpA->setColor(Color3B::YELLOW);
		SpB->setColor(Color3B::YELLOW);
	}
}
void  ContactListener::EndContact(b2Contact*contact)
{
	log("EndContact");
	b2Body* bodyA=contact->GetFixtureA()->GetBody();
	b2Body* bodyB=contact->GetFixtureB()->GetBody();
	auto SpA = (Sprite*)bodyA->GetUserData();
	auto SpB = (Sprite*)bodyB->GetUserData();
	if(SpA != nullptr && SpB!=nullptr)
	{
		SpA->setColor(Color3B::WHITE);
		SpB->setColor(Color3B::WHITE);
	}
}
void  ContactListener::PreSolve(b2Contact*contact ,const b2Manifold* oldmanifold)
{
	log("PreSolve");
}
void  ContactListener::PostSolve(b2Contact*contact,const b2ContactImpulse*impulse)
{
	log("PostSolve");
}