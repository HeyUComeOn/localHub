#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::~HelloWorld()
{
	//delete(world);
	CC_SAFE_DELETE(world);//避免了野指针，可谓二合一
	CC_SAFE_DELETE(contactListener);
}

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

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

	// 初始化物理引擎
	this->initPhysics();

	this->setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//
	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt)
{
	//此处代码基本固定

	//dt不稳定，重新定义timeStep
	float timeStep	=	0.03f;
	int32 velocityIterations = 8;
	int32 positionIterations = 1;

	world->Step(timeStep, velocityIterations, positionIterations);

	for (b2Body* b =world->GetBodyList(); b; b=b->GetNext())
	{
		if(b->GetUserData()!=nullptr)
		{
			Sprite*sprite = (Sprite*)b->GetUserData();
			sprite->setPosition(Vec2(b->GetPosition().x *PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			//CC_RADIANS_TO_DEGREES：将弧度转换为度，精灵用“°”
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));//-1:物理世界与精灵旋转方向相反
		}
	}
}

//创建世界和指定世界的边界
void HelloWorld::initPhysics()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//设置重力（水平为0）
	b2Vec2 gravity;
	gravity.Set(0.0f,-10.0f);
	//创建世界
	world = new b2World(gravity);
	//允许物体休眠（减少绘制的负担）
	world->SetAllowSleeping(true);
	//开始连续物理测试(放穿透)
	world->SetContinuousPhysics(true);
	//定义物理世界的边界(--Def:结构体)
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);

	//创建地面物体
	b2Body* groundBody=world->CreateBody(&groundBodyDef);

	//创建形状
	b2EdgeShape groundBox;

	//定义它的底部
	groundBox.Set(b2Vec2(0,0),b2Vec2(visibleSize.width/PTM_RATIO,0));

	//使用夹具固定形状到物体
	//此处开始报错是因为参数写成了双括号
	groundBody->CreateFixture(&groundBox,0);//第二个参数为密度，此处底部不用考虑重量

	//定义顶部
	groundBox.Set(b2Vec2(0,visibleSize.height/PTM_RATIO),b2Vec2(visibleSize.width/PTM_RATIO,visibleSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	//定义左边
	groundBox.Set(b2Vec2(0,visibleSize.height/PTM_RATIO),b2Vec2(0,0));
	groundBody->CreateFixture(&groundBox,0);

	//定义右边
	groundBox.Set(b2Vec2(visibleSize.width/PTM_RATIO,visibleSize.height/PTM_RATIO),b2Vec2(visibleSize.width/PTM_RATIO,0));
	groundBody->CreateFixture(&groundBox,0);
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto p=touch->getLocation();
	addNewSpriteAtPos(p);
	return true;
}

void HelloWorld::addNewSpriteAtPos(Vec2 pos)
{
	//创建物理相关的精灵
	auto sp=Sprite::create("BoxA2.png");
	sp->setPosition(pos);
	this->addChild(sp);

	//定义物体
	b2BodyDef bodyDef;
	bodyDef.type=b2_dynamicBody;
	bodyDef.position.Set(pos.x/PTM_RATIO,pos.y/PTM_RATIO);

	//物体精灵联系
	b2Body *body = world->CreateBody(&bodyDef);
	body->SetUserData(sp);

	//定义一个形状4平方米的盒子
	//Polygon:多边形
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1,1);//中心到右边界的距离

	//定义夹具
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	//将夹具固定到物体上
	body->CreateFixture(&fixtureDef);

}

