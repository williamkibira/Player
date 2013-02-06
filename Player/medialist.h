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


#ifndef MEDIALIST_H
#define MEDIALIST_H
#include<string>
class MediaList
{

public:
    MediaList();
    virtual ~MediaList();



    // our linked list single node..
    struct node {

        int track;
        //char *path;
       // char *name;
	std::string path;
	std::string name;

        node* next;
        node* prev;

    } node;


    // the methods to be exposed outside the class
    void pushIn(int track,std::string path, std::string name);
    std::string find_item(int index);
    std::string find_next_item(int index);
    std::string find_prev_item(int index);
    void print_data();
    void init();
private:

// the actual manipulation methods that will be kept in-house



    void insert(struct node *pointer, int track,char *path, char *name);
    std::string find_index(struct node *pointer , int index);
    std::string find_prev(struct node *pointer, int index);
    std::string find_next(struct node *pointer, int index);
    void print(struct node *pointer);
    // the action nodes that are to be manipulated
    struct node *start; //= new(struct node) ;
    struct node *temp; //= new(struct node);

};

#endif // MEDIALIST_H
