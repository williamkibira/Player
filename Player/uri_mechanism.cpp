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


#include "uri_mechanism.h"
#include <iostream>
#include "mediastore.h"
#include "medialist.h"
#include <stdlib.h>
#include <string.h>
#include <gtkmm-3.0/gtkmm/filechooser.h>
URI_Mechanism::URI_Mechanism()
{
    
}
void URI_Mechanism::filechoose()
{   static Glib::ustring working_dir = Glib::get_home_dir();
    Gtk::FileChooserDialog dialog("Please choose file",Gtk::FILE_CHOOSER_ACTION_OPEN);
    //dialog.set_transient_for(*this);
    //Add Response Buttons to the dialog
    dialog.add_button(Gtk::Stock::CANCEL,Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:

    
    //Show the dialog and wait for a user response:

    int result = dialog.run();

    //Handle the response:
    switch(result)
    {
    case(Gtk::RESPONSE_OK):
    {
        std::cout << "Open clicked." << std::endl;

        //Notice that this is a std::string, not a Glib::ustring.
        
         //dialog.set_current_folder(working_dir);
	 //std::string filename = dialog.get_uri(); 
	std::string filename = dialog.get_filename(); 
	
        std::cout << "File selected: " <<  filename << std::endl;
	// Collect the URI from here for a single file.
		std::vector<std::string> filenames;
		filenames.push_back(filename);
		fileIterator(filenames);
        break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
        std::cout << "Cancel clicked." << std::endl;
        break;
    }
    default:
    {
        std::cout << "Unexpected button clicked." << std::endl;
        break;
    }
    }

}

void URI_Mechanism::folderchoose()
{   static Glib::ustring working_dir = Glib::get_home_dir();
    Gtk::FileChooserDialog dialog("Please choose a folder",Gtk::FILE_CHOOSER_ACTION_OPEN
                                  /*Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER*/);
    //dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    int result = dialog.run();

    //Handle the response:
    switch(result)
    {
    case(Gtk::RESPONSE_OK):
    {    //dialog.set_current_folder(working_dir);
        std::cout << "Select clicked." << std::endl;
        //std::cout << "Folder selected: " << dialog.get_filename()<< std::endl;	
        //dialog.get_filenames();
                		//dialog.get_uris();
			//fileIterator( *dialog.get_filenames());
		dialog.set_select_multiple(true);
		dialog.select_all();

		std::vector<std::string> filenames (dialog.get_filenames());
		
		// Test for the aquired product
		/*
 		for(std::vector<std::string>::iterator iter = filenames.begin(); iter != filenames.end(); ++iter){
	        
             std::cout << *iter <<std::endl;
			}	
		*/
			//fileIterator(dialog.get_uris());
			fileIterator(filenames);

        break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
        std::cout << "Cancel clicked." << std::endl;
        break;
    }
    default:
    {
        std::cout << "Unexpected button clicked." << std::endl;
        break;
    }
    }
}

void URI_Mechanism::fileIterator(std::vector<std::string>& v)
{
    // feel free to add more file extensions :)
    char *extension[] = { ".mp3",".mp4",".mkv",".mpg",".avi",".ogg",".flac",".flv"};
    MediaList list;
    MediaStore store;
    counter = 0;

    // Iterate through the vector and load the URIS and filenames
    for(std::vector<std::string>::iterator iter = v.begin(); iter != v.end(); ++iter) {
        // Now run through the vector like a fool :)
		
	std::cout << "Test zone 2"<<std::endl;
        std::cout << *iter <<std::endl;
	
	std::string pathnamex ;
	pathnamex = std::string(*iter);
        // call a function to come and collect the garbage :)
	std::cout<< "I am here" <<std::endl;
        // first we check if the file types are OK
        // i am lazy so i am just going to iterate through the extensions
        for(int i = 0; i < (sizeof(extension)/sizeof(char*)); i++) {
		
            if(fileTypeFilter(pathnamex,extension[i]) == true)
            {   counter++;
	
                
		
                store.getDataToDB(counter,std::string(*iter),filename(std::string(*iter)));
                //list.pushIn(counter,std::string(*iter),filename(std::string(*iter)));
		
		
		
		


            }
        } 
    }

}
std::string URI_Mechanism::filename(std::string Dir)
{
    

    char FileName[200];
    char *FilePath;
    char *path;

    char *sp = strrchr(&Dir[0],'/');

    memset(FileName,0,sizeof(FileName));

    strncpy(FileName,sp+1, sizeof(FileName) - 1);

    //return std::string(filex);

    return std::string(FileName);

}


bool URI_Mechanism::fileTypeFilter(std::string filename, char *extension)
{
    // starts here

    char *filename_cstring = new char[sizeof(&filename[0])];
    filename_cstring = &filename[0];

    if(filename_cstring == NULL || extension == NULL)
        return false;

    if(strlen(filename_cstring) == 0 || strlen(extension) == 0)
        return false;

    if(strchr(filename_cstring, '.') == NULL || strchr(extension, '.') == NULL)
        return false;

    /* Iterate backwards through respective strings and compare each char one at a time */

    for(int i = 0; i < strlen(filename_cstring); i++)
    {
        if(tolower(filename_cstring[strlen(filename_cstring) - i - 1]) == tolower(extension[strlen(extension) - i - 1]))
        {
            if(i == strlen(extension) - 1)
                return true;
        } else
            break;
    }

    return false;


    // stops here
}

URI_Mechanism::~URI_Mechanism()
{

}

