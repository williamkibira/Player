/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef URI_MECHANISM_H
#define URI_MECHANISM_H
#include <gtkmm-3.0/gtkmm.h>

#include <string>
#include <vector>
class URI_Mechanism
{
// looks like this will be handled completely using a GUI , hmm, no choice
public:
    URI_Mechanism();

    void filechoose();
    void folderchoose();
    void fileIterator(std::vector <std::string> & v);
    bool fileTypeFilter(std::string filename,char *extension);
    std::string filename(std::string Dir);
    virtual ~URI_Mechanism();
    int counter;
};

#endif // URI_MECHANISM_H
