#include "CommandCreateLine.h"
#include "Data.h"
#include "File.h"
#include "LineShape.h"
#include "UserInterface.h"

CommandCreateLine::CommandCreateLine() : initial(Point()),final(Point()) {}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::exec(Data& data,UserInterface& ui)
{
   if (data.hasFile()) {
      id= data.getCurrentFile().generateIdShape();
      ui.markLineOptionAsSelected();
   }
   else
      ui.markOffAllOptions();
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::posMousePress(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   initial= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
   ui.activateMouseTracking();
}

void CommandCreateLine::posMouseMove(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   final= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));
   draw(ui,dataViewController,LineShape(id,initial,final));
}

void CommandCreateLine::posMouseRelease(Point& point,Data& data,UserInterface& ui)
{
   auto dataViewController= data.getCurrentFile().getDataViewController();
   final= dataViewController.fixPointViewInWorld(dataViewController.fixScroll(point));

   Shape& line= saveShapeOnFile(data);
   draw(ui,dataViewController,line);
}

///////////////////////////////////////////////////////////////////////////////

void CommandCreateLine::prepareToNewDraw(Data& data)
{
   id= data.getCurrentFile().generateIdShape();
}

Shape& CommandCreateLine::saveShapeOnFile(Data& data)
{
   LineShape* line= new LineShape(id,initial,final);
   data.getCurrentFile().addShapeOnFile(line);
   prepareToNewDraw(data);
   return *line;
}
