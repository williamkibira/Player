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


#include "mediastore.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "GUI_Code/playlistview.h"

void MediaStore::writeToDB()
{
    sqlite3 *db;

    int rc = sqlite3_open("media_data.db", &db);

    std::string sql_Init_Stmt = "CREATE TABLE IF NOT EXISTS music_list(track_index INT PRIMARY KEY,track_name TEXT,track_path TEXT)";

    rc = sqlite3_exec(db,sql_Init_Stmt.c_str(),NULL,NULL,NULL);
    if(rc!=SQLITE_OK) {

        std::cout<<"query error"<<sqlite3_errmsg(db);

    }
    sqlite3_stmt *insertstmt = NULL;

    std::string sql_insert_Stmt = "INSERT INTO  music_list(track_index,track_name,track_path) VALUES(:track_index,:track_name,:track_path)";
    printf("SQL_Track here\n");
    rc = sqlite3_prepare_v2(db,sql_insert_Stmt.c_str(),-1,&insertstmt,NULL);

    if(rc!=SQLITE_OK) {

        std::cout<<sqlite3_errmsg(db);
    }
    rc = sqlite3_bind_int(insertstmt,1,index_db);

    if(rc!=SQLITE_OK) {

        std::cout<<"query error"<<sqlite3_errmsg(db);
    }
    rc = sqlite3_bind_text(insertstmt,2,name_db,-1,SQLITE_STATIC);

    if(rc!=SQLITE_OK) {

        std::cout<<"query error"<<sqlite3_errmsg(db);
    }
    rc = sqlite3_bind_text(insertstmt,3,path_db,-1,SQLITE_STATIC);

    if(rc!=SQLITE_OK) {

        std::cout<<"query error"<<sqlite3_errmsg(db);
    }

    rc = sqlite3_step(insertstmt);

    if(rc != SQLITE_DONE && rc!=SQLITE_OK) {
        std::cout<<"query error"<<sqlite3_errmsg(db);
    }

    rc = sqlite3_finalize(insertstmt);

    rc = sqlite3_close(db);

    printf("The DB write\n");
}

/* Done writing to the database by the call*/

void MediaStore::readToDB()
{
    sqlite3 *db;
    int index;
    char *name;
    char *path;
// Create collection point here

     // create instance of playlist 
     PlaylistViewer loadplaylist;
	


    int rc = sqlite3_open("media_data.db", &db);

    std::string sqlQuery = "SELECT *FROM music_list";
    sqlite3_stmt *statement;

    rc = sqlite3_prepare_v2(db,sqlQuery.c_str(),-1,&statement,NULL);
//rc = sqlite3_reset(statement);

//sqlite3_bind_text(statement,1,[],-1,SQLITE_TRANSIENT);
    if(rc==SQLITE_OK) {
        printf("Data base produce\n");
        while(sqlite3_step(statement)== SQLITE_ROW) {
            index =(int)sqlite3_column_int(statement,0);
            name = (char*)sqlite3_column_text(statement,1);
            path = (char*)sqlite3_column_text(statement,2);

// transport the data into a linked list.

            printf("Test read number %d\n", index);
            printf("Test read name %s\n", name);
            printf("Test read path %s\n", path);

// collect the data here
		//loadplaylist.get_media_data( index, path,name);
// and load the vector to

		 playlistdata data = {index ,std::string(name),std::string(path)};
		 media_data.push_back(data);
	
        }


    }
    else {
        std::cout<<"query error"<<sqlite3_errmsg(db);
    }
    rc = sqlite3_finalize(statement);
    sqlite3_close(db);

}
/* done reading entire database */
void MediaStore::eraseDB()
{

    sqlite3 *db;
    int rc = sqlite3_open("media_data.db",&db);
    std::string sql_Delete_statement = "DROP TABLE music_list";
    rc = sqlite3_exec(db,sql_Delete_statement.c_str(),NULL,NULL,NULL);
    if(rc != SQLITE_OK) {
        std::cout<<"query error"<<sqlite3_errmsg(db);


    }
    sqlite3_close(db);
}
/* Done deleting all the data from the database. */

void MediaStore::deleteTrackFromDB(int index)
{
    sqlite3 *db;
    sqlite3_stmt *statement;
    int rc = sqlite3_open("media_data.db",&db);

    rc = sqlite3_prepare_v2(db,"DELETE ROW WHERE track_index = :index",-1,&statement,NULL);
    if(rc!=SQLITE_OK) {

        std::cout<<"query error"<<sqlite3_errmsg(db);
    }
    rc = sqlite3_bind_int(statement,1,index);
    if(rc!=SQLITE_OK) {

        std::cout<<"query error"<<sqlite3_errmsg(db);
    }

    rc = sqlite3_step(statement);

    if(rc != SQLITE_DONE && rc!=SQLITE_OK) {
        std::cout<<"query error"<<sqlite3_errmsg(db);
    }

    sqlite3_finalize(statement);

    rc = sqlite3_close(db);
}

void MediaStore::getDataToDB(int index, std::string path, std::string name)
{

    index_db = index;
    path_db = &path[0];
    name_db = &name[0];
    writeToDB();
}
std::vector<MediaStore::playlistdata> MediaStore:: sendData(){

return media_data;
}

