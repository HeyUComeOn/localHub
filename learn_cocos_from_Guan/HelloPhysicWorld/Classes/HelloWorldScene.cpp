#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto body=PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,5.0f);
	auto edgeNode=Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	
	this->setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//
    return true;
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto p=touch->getLocation();
	addNewSpriteAtPos(p);
	return true;
}

void HelloWorld::addNewSpriteAtPos(Vec2 pos)
{
	auto ball=Sprite::create("Ball.png");
	auto body=PhysicsBody::createCircle(ball->getContentSize().width/2);
	//将小球与物理引擎中的物体绑定
	ball->setPhysicsBody(body);
	ball->setPosition(pos);
	this->addChild(ball);
}
