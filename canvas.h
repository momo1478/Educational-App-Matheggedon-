#ifndef CANVAS_H
#define CANVAS_H

#include "qsfmlcanvas.h"

class Canvas : public QSFMLCanvas
{
public :
    Canvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size, 1000)
    {

    }

private :

    void OnInit();

    void OnUpdate();

    sf::Texture  myImage;
    sf::Sprite mySprite;
};

#endif // CANVAS_H
