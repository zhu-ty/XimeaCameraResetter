// include std
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <thread>
#include <memory>

#ifdef WIN32
#include <windows.h>
#include "xiApi.h"       // Windows
#else
#include <m3api/xiApi.h> // Linux, OSX
#endif

#define checkXIMEAErrors(val)  checkXIMEAInternal ( (val), #val, __FILE__, __LINE__ )

void checkXIMEAInternal(XI_RETURN result, char const *const func,
	const char *const file, int const line) 
{
	if (result != XI_OK) 
	{
		char info[256];
		sprintf(info, "XIMEA camera error at %s:%d function: %s\n",
			file, line, func);
		std::cout <<info <<std::endl;
	}
}

int main(int argc, char* argv[]) 
{
	PDWORD pnum = new DWORD;
	checkXIMEAErrors(xiGetNumberDevices(pnum));
	int num = *pnum;
	std::vector<HANDLE> hcams;
	hcams.resize(num);
	printf("%d XIMEA cameras detected\n", num);
	for (size_t i = 0; i < num; i++)
	{
		checkXIMEAErrors(xiOpenDevice(i, &hcams[i]));
	}
	printf("Camera Opened\n");
	for (size_t i = 0; i < num; i++)
	{
		checkXIMEAErrors(xiSetParamInt(hcams[i], XI_PRM_DEVICE_RESET, 1));
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout << "Suc!\nPress any key to continue..." << std::endl;
	getchar();
	return 0;
}

