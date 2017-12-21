#include <QPoint>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>

#include "App.h"
#include "MainWindow.h"
#include "NewDrawPopup.h"
#include "UserInterface.h"

std::string UserInterface::requestPathFileToSave(std::string fileName)
{
   const char* a = fileName.c_str();
   QString path = QFileDialog::getSaveFileName(this,tr("Salvar"),
      a,
      tr("Custom(.cad);"));

   return path.toStdString();
}

std::string UserInterface::requestPathFileToOpen()
{
   QString path = QFileDialog::getOpenFileName(this);

   return path.toStdString();
}

void UserInterface::showErrorMessage(std::string _message)
{
   const char* message = _message.c_str();
   QMessageBox::warning(this,QString::fromLatin1("Aten��o"),QString::fromLatin1(message),
      QMessageBox::StandardButton::Ok);
}

bool UserInterface::confirmOperation(std::string _message)
{
   const char* message = _message.c_str();
   QMessageBox::StandardButton response;
   response = QMessageBox::question(this,QString::fromLatin1("Aten��o"),QString::fromLatin1(message),
      QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);

   return (response == QMessageBox::Yes) ? true : false ;
}

NEW_FILE_STRUCTURE UserInterface::showPopupNewFile()
{
   NEW_FILE_STRUCTURE nfs;
   
   NewDrawPopup ndp(&nfs);
   ndp.exec();
   
   return nfs;
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startCreateArc()
{ 
   app.startCommandDrawArc();
}

void UserInterface::startCreateLine()
{ 
   app.startCommandDrawLine();
}

void UserInterface::startCreateBezier()
{ 
   app.startCommandDrawBezier();
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::mouseMoveEventInDrawArea(QPoint point) 
{ 
   app.actionMouseMoveInDrawArea(point.x(),point.y()); 
}

void UserInterface::mousePressEventInDrawArea(QPoint point) 
{ 
   app.actionMousePressInDrawArea(point.x(),point.y());
}

void UserInterface::mouseReleaseEventInDrawArea(QPoint point) 
{ 
   app.actionMouseReleaseInDrawArea(point.x(),point.y()); 
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startOptionNewFile() 
{ 
   app.startCommandNewFile(); 
}

void UserInterface::startOptionOpenFile()
{ 
   app.startCommandOpenFile(); 
}

void UserInterface::startOptionSaveFile()
{ 
   app.startCommandSaveFile();
}

void UserInterface::startOptionSaveAsFile()
{ 
   app.startCommandSaveAsFile();
}

void UserInterface::startOptionQuit()
{ 
   app.startCommandQuit();
}

///////////////////////////////////////////////////////////////////////////////

void UserInterface::startZoomValueChange(int value)
{ 
   app.startCommandZoomValueChange(value);
}
