#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::~HelloWorld()
{
	//delete(world);
	CC_SAFE_DELETE(world);//������Ұָ�룬��ν����һ
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

	// ��ʼ����������
	this->initPhysics();

	this->setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//
	this->scheduleUpdate();
	return true;
}

void HelloWorld::update(float dt)
{
	//�˴���������̶�

	//dt���ȶ������¶���timeStep
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
			//CC_RADIANS_TO_DEGREES��������ת��Ϊ�ȣ������á��㡱
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));//-1:���������뾫����ת�����෴
		}
	}
}

//���������ָ������ı߽�
void HelloWorld::initPhysics()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//����������ˮƽΪ0��
	b2Vec2 gravity;
	gravity.Set(0.0f,-10.0f);
	//��������
	world = new b2World(gravity);
	//�����������ߣ����ٻ��Ƶĸ�����
	world->SetAllowSleeping(true);
	//��ʼ�����������(�Ŵ�͸)
	world->SetContinuousPhysics(true);
	//������������ı߽�(--Def:�ṹ��)
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);

	//������������
	b2Body* groundBody=world->CreateBody(&groundBodyDef);

	//������״
	b2EdgeShape groundBox;

	//�������ĵײ�
	groundBox.Set(b2Vec2(0,0),b2Vec2(visibleSize.width/PTM_RATIO,0));

	//ʹ�üо߹̶���״������
	//�˴���ʼ��������Ϊ����д����˫����
	groundBody->CreateFixture(&groundBox,0);//�ڶ�������Ϊ�ܶȣ��˴��ײ����ÿ�������

	//���嶥��
	groundBox.Set(b2Vec2(0,visibleSize.height/PTM_RATIO),b2Vec2(visibleSize.width/PTM_RATIO,visibleSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	//�������
	groundBox.Set(b2Vec2(0,visibleSize.height/PTM_RATIO),b2Vec2(0,0));
	groundBody->CreateFixture(&groundBox,0);

	//�����ұ�
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
	//����������صľ���
	auto sp=Sprite::create("BoxA2.png");
	sp->setPosition(pos);
	this->addChild(sp);

	//��������
	b2BodyDef bodyDef;
	bodyDef.type=b2_dynamicBody;
	bodyDef.position.Set(pos.x/PTM_RATIO,pos.y/PTM_RATIO);

	//���徫����ϵ
	b2Body *body = world->CreateBody(&bodyDef);
	body->SetUserData(sp);

	//����һ����״4ƽ���׵ĺ���
	//Polygon:�����
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1,1);//���ĵ��ұ߽�ľ���

	//����о�
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	//���о߹̶���������
	body->CreateFixture(&fixtureDef);

}

