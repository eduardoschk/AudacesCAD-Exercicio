#pragma once
#ifndef INCLUDED_IO_FILE_H
#define INCLUDED_IO_FILE_H

#include <string>
#include "Coordinate.h"

class File;
class Shape;

class IOFile
{
private:
   void writeShape(std::ofstream& stream,Shape& shape);
   void writeCoordinate(std::ofstream& stream,Coordinate coordinate);

   Shape* readShape(int id,std::ifstream& stream);
   Coordinate readCoordinate(std::ifstream& stream);
   Shape* readArcShape(int id,std::ifstream& stream);
   Shape* readLineShape(int id,std::ifstream& stream);
   Shape* readBezierShape(int id,std::ifstream& stream);

   void save(std::ofstream& stream,File& file);
public:
   ~IOFile() {}
   IOFile() {}

   bool save(File& file);
   void saveAs(std::string completedPath,File& file);
   File* open(std::string pathAndFile);

};

#endif // INCLUDED_IO_FILE_H