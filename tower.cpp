#include "tower.h"

Tower::Tower(int x, int y, int w, int h, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    width = w;
    height = h;
    world = worldb2;

    health = 1000;

    createTowerBox2D();
}

Tower::~Tower()
{

}

QRectF Tower::boundingRect() const
{
     return QRectF(0,0,width*30,height*30);
}

void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(0, 0, width*2, height*2, QBrush(Qt::gray));
    //painter->drawRect(0, 0, width*2, height*2);

    painter->drawLine(-220, height*2, width*2+220, height*2);
}

void Tower::timerEvent(QTimerEvent *event)
{

}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Tower::createTowerBox2D()
{
    //Tower Position
    b2BodyDef towerBodyDef;
    towerBodyDef.type = b2_staticBody;
    towerBodyDef.position.Set(xPos, yPos);
    b2Body* towerBody = world->CreateBody(&towerBodyDef);

    towerBody->SetUserData(this);

    //Tower Shape
    b2PolygonShape towerShape;
    towerShape.SetAsBox(width, height);

    //Tower Fixture
    b2FixtureDef towerFixtureDef;
    towerFixtureDef.shape = &towerShape;
    towerFixtureDef.density = 1;
    towerBody->CreateFixture(&towerFixtureDef);
}

void Tower::decreaseHealth()
{
    health = health - 100;
    std::cout << "Health of Tower: " << health << std::endl;
    QPainter painter;
    painter.fillRect(0, 0, width*2, height*2, QBrush(Qt::red));
}
