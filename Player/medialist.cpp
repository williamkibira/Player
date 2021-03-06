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


#include "medialist.h"
#include <stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
MediaList::MediaList()
{
    start = NULL;
}

MediaList::~MediaList()
{

}
void  MediaList::insert(struct node *pointer, int track,char *path, char *name)
{

    /* Iterate through the list till we encounter the last node.*/
    while(pointer->next!= NULL)
    {
        pointer = pointer -> next;
    }
    /* Allocate memory for the new node and put data in it.*/
    pointer->next = new(struct node);
    (pointer->next)->prev = pointer;
    pointer = pointer->next;
    pointer->track = track;
   // pointer->path = new char[sizeof(path)];
   // pointer->name = new char[sizeof(name)];
	pointer->path = std::string(path);
	pointer->name = std::string(name);

   // strcpy(pointer->path,path);
    //strcpy(pointer->name ,name);
    pointer->next = NULL;

 // delete the arrays on site
	
	

}



std::string MediaList::find_index(struct node *pointer, int index)
{
    if(pointer!= NULL) {
        std::cout << "chedking node " << pointer->track << std::endl;
        if(pointer->track == index) {
            printf("Survive 0 \n");
            return (pointer->path);
        } else {
            // recursion
            return(find_index(pointer->next,index));
        }
        // this should never run
        printf("Survive 1 \n");
    }

}


std::string MediaList::find_prev(struct node *pointer, int index)
{

    if(pointer!= NULL) {
        if(pointer->track == index) {
            return ((pointer->prev)->path);
        } else {
            return(find_prev(pointer->next,index));
        }
    }

}

std::string MediaList::find_next(struct node *pointer, int index)
{

    if(pointer!= NULL) {
        if(pointer->track == index) {
            return((pointer->next)->path);
        } else {
            return(find_next(pointer->next,index));
        }
    }
}

void MediaList::print(struct node *pointer)
{
    if(pointer==NULL)
    {
        return;
    }
    else if(pointer->path.empty()) {
//print(pointer->next);

        return ;
    }
    else {
        std::cout<<pointer->track<<std::endl;
        std::cout<<(pointer->path)<<std::endl;
        std::cout<<(pointer->name)<<std::endl;
        print(pointer->next);
    }
}



// Mask function definitions

void MediaList::pushIn(int track,std::string path, std::string name)
{    
     
    if(start) {
        insert(start,track,&path[0],&name[0]);
    } else {
        start = new (struct node);
        start->prev = NULL;
        start->next = NULL;
        start->track = track;
        start->path = path;
        start->name = name;
    }
	std::cout<<"Done writing to list"<<std::endl;
	
}

std::string MediaList::find_next_item(int data)
{
    if(!start)
        std::cout << "missing nodes!"<< std::endl;
    std::string result = find_next(start, data);
    std::cout<< result << std::endl;
    return result;
}

std::string MediaList::find_prev_item(int data)
{

    if(!start)
        std::cout << "missing nodes!"<< std::endl;
    std::string result = find_prev(start, data);
    std::cout <<result << std::endl;
    return result;
}

std::string MediaList::find_item(int data)
{
    if(!start)
        std::cout << "missing nodes!" << std::endl;
    std::string result = find_index(start,data);
    std::cout << result << std::endl;
    std::cout << "done?" << std::endl;
    return result;
}

void MediaList::print_data()
{
    print(start);
}



