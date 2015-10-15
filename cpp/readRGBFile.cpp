//  LED-Painter, to draw live on a LED-Matrix
//  Copyright (C) 2015 Dominik Meier(XPerianer)
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  E-Mail: Hiscore.pressthebutton@hotmail.de




#include "readRGBFile.h"

  Canvas *canvas;
  GPIO io;

 struct color {
   int r,g,b;
 };



int main(){
    if (!io.Init()){
      std::cout << "Initalisieren fehlgeschlagen" << std::endl;
      }

      canvas = new RGBMatrix(&io, 32, 1, 1);
      std::cout << "Initalisation finished" << std::endl;

      readRGBFile(canvas,"test.rgb");

      std::cout << "Press Enter to abort" << std::endl;
      getchar();

      canvas->Clear();

      return 1;

  }



  int readRGBFile(Canvas* canvas,std::string path){
    color matrix[32][32];

    std::ifstream file;
    file.open(path);
    if(file.is_open()){
      std::cout << "File successfully opened" << std::endl;

      try{
      for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
          std::string help="";

          file >> help;
          matrix[i][j].r = std::stoi(help);
          help = "";

          file >> help;
          matrix[i][j].g = std::stoi(help);
          help = "";

          file >> help;
          matrix[i][j].b = std::stoi(help);

        }
      }
    }

    catch(...){
      std::cout << "Error at reading the File " << std::endl;
      return 0;
    }

  }

  for(int i=0;i<32;i++){
    for(int j=0;j<32;j++){
      canvas->SetPixel(i,j,matrix[i][j].r,matrix[i][j].g,matrix[i][j].b);
    }
  }
  return 1;
}
