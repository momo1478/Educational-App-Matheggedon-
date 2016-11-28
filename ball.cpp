#include "ball.h"

Ball::Ball(int x, int y, int r, b2World* worldb2)
{
    xPos = x;
    yPos = y;
    rad = r;
    world = worldb2;

    createBallBox2D();
}



QRectF Ball::boundingRect() const
{
     return QRectF(0,0,20,20);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::blue, 5);
    painter->setPen(pen);
    painter->drawEllipse(xPos, yPos, rad, rad);
}

void Ball::timerEvent(QTimerEvent *event)
{

}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Ball::createBallBox2D()
{
    //Ball Position
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(xPos, yPos);
    ballBodyDef.awake = true;
    body = world->CreateBody(&ballBodyDef);

    //Ball Shape
    b2CircleShape ballShape;
    ballShape.m_radius = rad;

    //Ball Fixture
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 1;
    ballFixtureDef.friction = 0;
    ballFixtureDef.restitution = 0.6f;
    body->CreateFixture(&ballFixtureDef);

    //Apply a force
    body->ApplyForce(b2Vec2(1000.0f, -500.0f), b2Vec2(0.0, 0.0f), false);
}

void Ball::move()
{
    //setPos(body->GetPosition().x, -body->GetPosition().y);
}


