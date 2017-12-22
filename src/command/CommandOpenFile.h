#pragma once
#ifndef INCLUDED_COMMAND_OPEN_FILE_H
#define INCLUDED_COMMAND_OPEN_FILE_H

#include "CommandIOFile.h"

class File;
class Shape;

class CommandOpenFile : public CommandIOFile
{
private:
   void drawShape(UserInterface& ui,Shape& shape);
   void drawOpenFile(UserInterface& ui,File& openedFile);
public:
   ~CommandOpenFile() {}
   CommandOpenFile() {}

   void exec(Data& data,UserInterface& ui);
};

#endif // INCLUDED_COMMAND_OPEN_H