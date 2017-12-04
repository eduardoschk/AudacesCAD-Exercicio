#pragma once
#ifndef INCLUDED_MAIN_WINDOW_H
#define INCLUDED_MAIN_WINDOW_H

#include <string.h>
#include <QMainWindow>

class QLabel;
class QSlider;
class DrawArea;
class UserInterface;

class MainWindow : public QMainWindow
{
   Q_OBJECT
private:
   UserInterface& ui;
   DrawArea* drawArea;

   QAction* arc;
   QAction* line;
   QAction* bezier;
   QSlider* sliderZoom;

   void configureDrawActions();
   void configureToolBarShapes();
   void configureZoomControlOnStatusBar();
   void configureMenuBar(QMenuBar& menuBar);
   void resizeEvent(QResizeEvent* event) override;

public:
   ~MainWindow();
   MainWindow(UserInterface& _ui,QWidget* parent= nullptr);

   void createNewDrawArea(int _width,int _heigth);

   void eraseDraw(int id);

   void drawLine(int id,QPoint initial,QPoint final);
   void drawArc(int id,QPoint center,QPoint initial,QPoint final);
   void drawBezier(int id,QPoint initial,QPoint control,QPoint final);

   void setShapArc();
   void setShapeLine();
   void setShapeBezier();

   void setDrawingScale(float scale);

public slots:
   void minusZoomClicked();
   void plusZoomClicked();
};

#endif // INCLUDED_MAIN_WINDOW_H