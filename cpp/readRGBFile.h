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


#include <iostream>
#include "led-matrix.h"
#include <fstream>
#include <string>
using namespace rgb_matrix;

int readRGBFile(Canvas* canvas,std::string path="test.rgb");
