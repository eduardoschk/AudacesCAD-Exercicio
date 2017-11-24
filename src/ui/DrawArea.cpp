#include "DrawArea.h"

#include <QtMath>
#include <QScrollBar>
#include <QMouseEvent>

#include "Line.h"
#include "Bezier.h"
#include "Arc.h"

int SIZE_SCROLL= 10;

DrawArea::~DrawArea() 
{
   for (int i= 0 ; i < itens.size() ; ++i)
      delete itens[i];;
   delete scene;
   if (hScrollBar)
      delete hScrollBar;
   if (vScrollBar)
      delete vScrollBar;
}

DrawArea::DrawArea(int _widthArea,int _heightArea,int _limitWidth,int _limitHeight)
{
   tempItem= nullptr;
   widthDraw= _widthArea;
   heightDraw= _heightArea;
   limitWidth=_limitWidth;
   limitHeight= _limitHeight;

   scene= new QGraphicsScene(this);

   configureDefaultValues();
   configureScrollBar();

   scene->setSceneRect(QRect(QPoint(0,0),QPoint(widthDraw,heightDraw)));
   changedSize();
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::configureDefaultValues()
{
   scale= 1;

   setScene(scene);

   setAutoFillBackground(true);
   setBackgroundRole(QPalette::Base);
}

void DrawArea::configureScrollBar()
{
   widthHorizontalScrollBar= heigthVerticalScrollBar= 0;

   hScrollBar= horizontalScrollBar();
   vScrollBar= verticalScrollBar();

   connect(hScrollBar,SIGNAL(valueChanged(int)),this,SLOT(widthScrollChanged(int)));
   connect(vScrollBar,SIGNAL(valueChanged(int)),this,SLOT(heightScrollChanged(int)));
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::setScale(float _scale)
{
   QMatrix ma;
   scale = _scale;
   ma.scale(qreal(scale),qreal(scale));
   setMatrix(ma);
   changedSize();
}

QPoint DrawArea::correctPointInRelationToScrollbar(QPoint point)
{
   return point+= QPoint(widthHorizontalScrollBar,heigthVerticalScrollBar);
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::changedSize()
{
   int widthReal= calcNewDrawingWidth();
   int heigthReal= calcNewDrawingHeight();

   setFixedSize(widthReal,heigthReal);
}

int DrawArea::calcNewDrawingWidth()
{
   return (SIZE_SCROLL + widthDraw * scale > limitWidth) ? limitWidth : (SIZE_SCROLL + widthDraw * scale);
}

int DrawArea::calcNewDrawingHeight()
{
   return (SIZE_SCROLL + heightDraw * scale > limitHeight) ? (limitHeight - SIZE_SCROLL) : (SIZE_SCROLL + heightDraw * scale) ;
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::heightScrollChanged(int value)
{
   heigthVerticalScrollBar = value;
}

void DrawArea::widthScrollChanged(int value)
{
   widthHorizontalScrollBar = value;
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::mousePressEvent(QMouseEvent* event)
{
   emit(mousePress(correctPointInRelationToScrollbar(event->pos()) / scale));
   setMouseTracking(true);
   event->accept();
}

void DrawArea::mouseMoveEvent(QMouseEvent* event)
{
   emit(mouseMove(correctPointInRelationToScrollbar(event->pos()) / scale));
   event->accept();
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event)
{
   emit(mouseRelease(correctPointInRelationToScrollbar(event->pos()) / scale));
   setMouseTracking(false);
   event->accept();
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::setLimitArea(const QSize size)
{
   limitWidth= size.width();
   limitHeight= size.height();
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::cleanTempItem()
{
   if (tempItem) {
      delete tempItem;
      tempItem= nullptr;
   }
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::drawTempLine(QPoint initial,QPoint final)
{
   cleanTempItem();
   tempItem= new Line(initial, final);
   scene->addItem(tempItem);
}

void DrawArea::drawTempBezier(QPoint initial,QPoint control,QPoint final)
{
   cleanTempItem();
   tempItem= new Bezier(initial,control,final);
   scene->addItem(tempItem);
}

void DrawArea::drawTempArc(QPoint center,QPoint initial,QPoint final)
{
   cleanTempItem();
   tempItem= new Arc(center,initial,final);
   scene->addItem(tempItem);
}

///////////////////////////////////////////////////////////////////////////////

void DrawArea::drawLine(QPoint initial,QPoint final)
{
   itens.push_back(new Line(initial, final));
   scene->addItem(itens.back());
   scene->update();
}

void DrawArea::drawBezier(QPoint initial,QPoint control,QPoint final)
{
   itens.push_back(new Bezier(initial,control,final));
   scene->addItem(itens.back());
   scene->update();
}

void DrawArea::drawArc(QPoint center,QPoint initial,QPoint final)
{
   itens.push_back(new Arc(center,initial,final));
   scene->addItem(itens.back());
   scene->update();
}