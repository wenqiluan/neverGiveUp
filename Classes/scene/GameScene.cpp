#include "GameScene.h"

USING_NS_CC;

/*
	screen size = 800 * 480
	�˶����̷�Ϊ2�����֣���һ������Ϊ��ʼ�����ֵ��˶�������10��λ�õĵף�Ȼ��ʼ����
*/

Scene* GameScene::createScene()
{

	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init(){
	if (!Layer::init()){
		return false;
	}
	//background picture
	auto bg = Sprite::create("bg.png");
	bg->setPosition(400, 240);
	this->addChild(bg, 0);


	auto t = Sprite::create("Green.png");
	t->setPosition(45+90*2, 100);
	this->addChild(t);
	t->setTag(0);
	auto cover = Sprite::create("Green.png");
	t->addChild(cover);
	cover->setPosition(48, 20);
	cover->setName("cover");
	cover->setVisible(false);

	for (int i = 1; i < 10; ++i){
		auto base1 = Sprite::create("Gray.png");
		base1->setPosition(45+90*i +90*2  , 100); //45+90*i
		base1->setTag(i);
		this->addChild(base1);

		auto cover = Sprite::create("Green.png");
		base1->addChild(cover);
		cover->setPosition(48, 20);
		//cover->setAnchorPoint(ccp(0.5, 0.5));
		cover->setName("cover");
		cover->setVisible(false);
	}
	this->count = 0;//��ʼ��


	
	

	///�����¼��Ĵ���

	this->setTouchEnabled(true);
	auto dispatcher = Director::getInstance()->getEventDispatcher();        
	auto listener = EventListenerTouchOneByOne::create();       

	listener->onTouchBegan = [=](Touch* touch, Event* event){
		CCLOG("touch began");
		Vec2 v = touch->getLocation();
		CCLOG("%f %f", v.x, v.y);
		jumpBall();//�����lambda���ʽ[]�м��롰=�����Ὣthis���룬���������lambda���ʽ�е��ú���������

		return true;//һ��Ҫ����true �����������¼����������
	};
	/*
	listener->onTouchMoved = [](Touch* touch, Event* event){
		CCLOG("touch moved");
		Vec2 v = touch->getLocation();
		CCLOG("%f %f", v.x, v.y);

	};
	listener->onTouchEnded = [=](Touch* touch, Event* event){
		CCLOG("touch ended");
	};
	*/
	listener->setSwallowTouches(true);//�����´��ݴ���       
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	//�����ľ�����ball
	auto ball = Sprite::create("Ball.png");
	ball->setTag(1000);
	ball->setName("ball");
	ball->setZOrder(1000);
	ball->setPosition(ccp(225, 136));
	ballHight = 136;
	this->addChild(ball);
	auto actionUp = JumpBy::create(5, Vec2(0, 0), 40, 10);
	ball->runAction(RepeatForever::create(actionUp));



	//this->scheduleOnce(schedule_selector(GameScene::action), 1.5);
	//���ù����¼�
	this->schedule(schedule_selector(GameScene::update), 0);//check positon each frames
	this->schedule(schedule_selector(GameScene::repeateAction), 5);
	this->schedule(schedule_selector(GameScene::judgeGame), 0.3);
	return true;
}


void GameScene::jumpBall(){
	auto ball = this->getChildByName("ball");
	if (ball->getPositionY() < ballHight + 20) // �˴�������Ϸ�Ѷ�
	{
		log("============jump ball");
		auto jumpAction = MoveBy::create(0.2, ccp(0, 40));
		ball->runAction(jumpAction);
		ballHight = ballHight + 40;
		//ball->setPositionY(170);
	}
}


void GameScene::action(float t){
	log("hehe");
	//��һ�ι������¼�
	for (int i = 0; i < 10; ++i){
		auto base = this->getChildByTag(i);
		if (!base){
			CCLOG("get child by tag  failed");
			break;
		}
		auto moveByAction = MoveBy::create(1.5, ccp(-270, 0));//�ƶ�������Ե�λ��
		base->runAction(moveByAction);
	}
}

void GameScene::update(float t){
	//���λ�ã����������ƶ���this update each frame
	for (int i = 0; i < 10; ++i){
		auto sprite = this->getChildByTag(i);
		if (sprite->getPositionX() <= 230){
			//CCLOG("add cover");
			auto t = sprite->getChildByName("cover");
			if (t){
				t->setVisible(true);
			}
		}
		if (sprite->getPositionX() <= -45)
		{
			
			float random = CCRANDOM_0_1();
			CCLOG("random = %f",random);
			if (random > 0.5){
				//������ɸ߶�
				if (preHeight < 4){
					sprite->setPosition(850, 100 + preHeight * 40);
					preHeight++;
				}
			}
			else{
				if (preHeight>0){
					sprite->setPosition(850, 100 + preHeight * 40);
					preHeight--;
				}
			}


			auto cover = sprite->getChildByName("cover");
			if (cover){
				//cover->release();
				CCLOG("release cover");
				cover->setVisible(false);
			}
		}

		
	}
}

void GameScene::repeateAction(float t){
	log("repeate");
	for (int i = 0; i < 10; ++i){
		auto sprite = this->getChildByTag(i);
		auto moveByAction = MoveBy::create(5, ccp(-900, 0));//�ƶ�������Ե�λ��,���ھ�ȷҪ�������ٶ�  180 pix / s
		sprite->runAction(moveByAction);
	}
}

void GameScene::judgeGame(float t){

	Node * sprite;
	for (int i = 0; i < 10; ++i){
		sprite = this->getChildByTag(i);
		if (sprite->getPositionX() >200 && sprite->getPositionX() < 250){
			break;
		}
	}
	int height = sprite->getPositionY();
	if (abs(ballHight - height) < 10){
		CCLOG("-----========stop!!!!");
		//��������ֹͣ��Ҫ�����schedule�������˲�ֹͣ
		this->unschedule(schedule_selector(GameScene::repeateAction));
		this->unschedule(schedule_selector(GameScene::judgeGame));

		// jump to another scene

	}


	
}
