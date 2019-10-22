#include "functionexample.h"
#include "FlyCapture2.h"
#include "toojpeg.h"
using namespace FlyCapture2;

unsigned char mybuffer[360960];
int count = 0;
Camera *tempcamera;
bool iscameraconnected = false;
int capturecount = 0;
int myserialnumber=0;
unsigned char fixedimage[360960];


void myOutput(unsigned char byte);
int connectcamera();
int capturecamera();
int disconnectcamera();


void myOutput(unsigned char byte)
{
	mybuffer[count] = byte;
	count++;
}

/*
void SaveBitmapToFile(BYTE *pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, const unsigned long &padding_size, LPCTSTR lpszFileName)
{
	// Some basic bitmap parameters
	unsigned long headers_size = sizeof(BITMAPFILEHEADER) +
								 sizeof(BITMAPINFOHEADER);

	unsigned long pixel_data_size = lHeight * ((lWidth * (wBitsPerPixel / 8)) + padding_size);

	BITMAPINFOHEADER bmpInfoHeader = {0};

	// Set the size
	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);

	// Bit count
	bmpInfoHeader.biBitCount = wBitsPerPixel;

	// Use all colors
	bmpInfoHeader.biClrImportant = 0;

	// Use as many colors according to bits per pixel
	bmpInfoHeader.biClrUsed = 0;

	// Store as un Compressed
	bmpInfoHeader.biCompression = BI_RGB;

	// Set the height in pixels
	bmpInfoHeader.biHeight = lHeight;

	// Width of the Image in pixels
	bmpInfoHeader.biWidth = lWidth;

	// Default number of planes
	bmpInfoHeader.biPlanes = 1;

	// Calculate the image size in bytes
	bmpInfoHeader.biSizeImage = pixel_data_size;

	BITMAPFILEHEADER bfh = {0};

	// This value should be values of BM letters i.e 0x4D42
	// 0x4D = M 0��42 = B storing in reverse order to match with endian
	bfh.bfType = 0x4D42;
	//bfh.bfType = 'B'+('M' << 8);

	// <<8 used to shift ��M�� to end  

	// Offset to the RGBQUAD
	bfh.bfOffBits = headers_size;

	// Total size of image including size of headers
	bfh.bfSize = headers_size + pixel_data_size;

	// Create the file in disk to write
	HANDLE hFile = CreateFile(lpszFileName,
							  GENERIC_WRITE,
							  0,
							  NULL,
							  CREATE_ALWAYS,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);

	// Return if error opening file
	if (!hFile)
		return;

	DWORD dwWritten = 0;

	// Write the File header
	WriteFile(hFile,
			  &bfh,
			  sizeof(bfh),
			  &dwWritten,
			  NULL);

	// Write the bitmap info header
	WriteFile(hFile,
			  &bmpInfoHeader,
			  sizeof(bmpInfoHeader),
			  &dwWritten,
			  NULL);

	// Write the RGB Data
	WriteFile(hFile,
			  pBitmapBits,
			  bmpInfoHeader.biSizeImage,
			  &dwWritten,
			  NULL);

	// Close the file handle
	CloseHandle(hFile);
}
*/




int setcursor(int x, int y)
{
	int a = SetCursorPos(x, y);
	return a;
}
POINT getcursor()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	return ptMouse;
}
int mouserightclick()
{
	INPUT Inputs[2] = {0};
	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	Inputs[1].type = INPUT_MOUSE;
	Inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

	SendInput(2, Inputs, sizeof(INPUT));
	return 1;
}

//!@#
int return_c_or_esc()
{
	while (1)
	{
		if (GetKeyState('C') & 0x8000)
		{
			//std::cout << "C누름";
			return 2;
		}
		else if (GetKeyState(27) & 0x8000)
		{
			//VK_ESCAPE   =  0x1B  =  int 27
			//std::cout << "ESC누름";
			return 3;
		}
		else if (GetKeyState(VK_LBUTTON) & 0x100)
		{
			//std::cout << "마우스 좌클릭함";
			return 4;
		}
	}
}

int mouseleftclick()
{
	INPUT Inputs[2] = {0};
	WORD findkey = VK_F12;

	Inputs[0].type = INPUT_MOUSE;
	Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	Inputs[1].type = INPUT_MOUSE;
	Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput(2, Inputs, sizeof(INPUT));
	return 1;
}
char keyboardpress(int keynum)
{

	INPUT input;
	//	 WORD vkey = VK_F12; // see link below

	//https://docs.microsoft.com/ko-kr/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
	//가상키코드
	input.type = INPUT_KEYBOARD;
	//	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = keynum;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	return (char)keynum;
}





int capturecamera()
{
	if (iscameraconnected == true)
	{
		Camera *camera = tempcamera;
		capturecount++;
		//std::cout << "capturecount:" << capturecount << std::endl;

		Image rawImage;
		Error error;
		error = camera->RetrieveBuffer(&rawImage); //RAWiMAGE
		if (error != PGRERROR_OK)
		{
			//std::cout << "capture error" << std::endl;
			return 0;
		}
		unsigned char *rawbyte = rawImage.GetData();

		//std::cout<<"rawbyte length:"<<rawImage.GetDataSize(); //480*752

		//좌우반전을위해....합니다..

		for (int j = 0; j < 480; j++)
		{
			for (int i = 0 + j * 752; i < 752 + j * 752; i++)
			{
				fixedimage[i] = rawbyte[751 - i + 752 * j * 2];
			}
		}

		const bool isRGB = false;					   // true = RGB image, else false = grayscale
		const int quality = 90;						   // compression quality: 0 = worst, 100 = best, 80 to 90 are most often used
		const bool downsample = true;				   // false = save as YCbCr444 JPEG (better quality), true = YCbCr420 (smaller file)
		const char *comment = "TooJpeg example image"; // arbitrary JPEG comment
		count = 0;

		//TooJpeg::writeJpeg(myOutput, &fixedimage[0], 752, 480, isRGB, quality, downsample, comment);
TooJpeg::writeJpeg(myOutput, fixedimage, 752, 480, isRGB, quality, downsample, comment);
		//std::cout << "ok";

		return 1;
	}
	else
	{
		//std::cout << "can't captrue! disconnected status" << std::endl;

		return 0;
	}
}

int disconnectcamera()
{
	if (iscameraconnected == true)
	{
		capturecount = 0;

		Camera *camera = tempcamera;
		Error error;
		error = camera->StopCapture();

		if (error != PGRERROR_OK)
		{
		//	std::cout << "Error disconnectcamera" << std::endl;
			// This may fail when the camera was removed, so don't show
			// an error message
		}
		camera->Disconnect();
		delete[] camera;
		iscameraconnected = false;
		//std::cout << "Success! disconnect to camera" << std::endl;
		return 1;
	}
	else
	{
	//	std::cout << "already disconnected status" << std::endl;
		return 0;
	}
}

int connectcamera()
{
	Camera *camera;
	Error error;
	if (iscameraconnected)
	{
	//	std::cout << "alerdy connect" << std::endl;
		return myserialnumber;
	}
	else
	{

	//	std::cout << "first connect" << std::endl;
		camera = new Camera();
		tempcamera = camera;

		error = camera->Connect(0);
		if (error != PGRERROR_OK)
		{
			//std::cout << "Failed to connect to camera" << std::endl;
			return 0;
		}
		else
		{
		//	std::cout << "1. Camera Connect Success" << std::endl;
		}

		// Get the camera info and print it out
		CameraInfo camInfo;
		error = camera->GetCameraInfo(&camInfo);
		if (error != PGRERROR_OK)
		{
		//	std::cout << "Failed to get camera info from camera" << std::endl;
			return 0;
		}
		else
		{
		//	std::cout << "2. Camera info" << std::endl;
		}

	//	std::cout << "3. -vendorName:" << camInfo.vendorName << " -modelName: "
	//			  << camInfo.modelName << " -serialNumber: "
	//			  << camInfo.serialNumber << std::endl;

		error = camera->StartCapture();
		if (error == PGRERROR_ISOCH_BANDWIDTH_EXCEEDED)
		{
	//		std::cout << "Bandwidth exceeded" << std::endl;
			return 0;
		}
		else if (error != PGRERROR_OK)
		{
		//	std::cout << "Failed to start image capture" << std::endl;
			return 0;
		}
		iscameraconnected = true;
		myserialnumber = camInfo.serialNumber; 
		return camInfo.serialNumber;
		//return 1;
	}

	/*
	// if you want to return pixel  set return type to  [unsinged char*]
		BYTE *abc = new BYTE[1082880]; //480*752*3
		for(int i = 0 ; i<1082880 ; i++)
		{
			abc[i] = rgbImagebyte[i];
		}

		return abc;
	*/
}



std::string functionexample::hello()
{
	return "Hello World!!!";
}

int functionexample::add(int a, int b)
{
	return a + b;
}

void functionexample::myfunction()
{

	std::cout << "in myfunction cout test" << std::endl;
}

void functionexample::MySleep(int num)
{
	Sleep(num);
}




Napi::Number Ispress_corescWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	return Napi::Number::New(env, return_c_or_esc());
}
Napi::Number keyboardpressWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	if (info.Length() != 1 || !info[0].IsNumber())
	{
		Napi::TypeError::New(env, "Number expected 65=a and please insert just 1 argument like this (example): testAddon.PressKeyboard(65); ").ThrowAsJavaScriptException();
	}

	Napi::Number first = info[0].As<Napi::Number>(); //unsig

	char returnValue = keyboardpress(first.Int32Value()); //unsigned short int

	return Napi::Number::New(env, returnValue);
}
Napi::Number mouseleftclickWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	if (info.Length() != 0)
	{
		Napi::TypeError::New(env, "need not argument ").ThrowAsJavaScriptException();
	}

	Napi::Number first = info[0].As<Napi::Number>();

	char returnValue = mouseleftclick();

	return Napi::Number::New(env, returnValue);
}
Napi::Number mouserightclickWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	if (info.Length() != 0)
	{
		Napi::TypeError::New(env, "need not argument ").ThrowAsJavaScriptException();
	}

	Napi::Number first = info[0].As<Napi::Number>();

	char returnValue = mouserightclick();

	return Napi::Number::New(env, returnValue);
}
Napi::Number SetCursorWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
	{
		Napi::TypeError::New(env, "two Number expected").ThrowAsJavaScriptException();
	}

	Napi::Number first = info[0].As<Napi::Number>();
	Napi::Number second = info[1].As<Napi::Number>();

	int returnValue = setcursor(first.Int32Value(), second.Int32Value());

	return Napi::Number::New(env, returnValue);
}

Napi::Array GetCursorWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	POINT mouseposition = getcursor();

	Napi::Array jsNativeArray = Napi::Array::New(env);
	jsNativeArray.Set("x", mouseposition.x);
	jsNativeArray.Set("y", mouseposition.y);

	return jsNativeArray;
}





Napi::Value capturecameraWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	capturecamera();

	Napi::Array jsNativeArray = Napi::Array::New(env);

	for (int i = 0; i < count; i++)
	{
		jsNativeArray.Set(i, mybuffer[i]);
	}
	return jsNativeArray;
}

Napi::Number disconnectcameraWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	return Napi::Number::New(env, disconnectcamera());
}

Napi::Number connectcameraWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	/*unsigned char* abc = connectcamera();
	LPCTSTR filename3 = TEXT("image_created3.bmp");
	SaveBitmapToFile(abc, 752, 480, 24, 0, filename3);
	*/
	int a = connectcamera();

	return Napi::Number::New(env, a);
	/*
	//#################Do not Delete very Important###################################
	if you want to return raw data, you should set return type to [Napi::Value]
	Napi::Array jsNativeArray = Napi::Array::New(env);
	for (int i = 0; i < 1082880; i++) {
		jsNativeArray.Set(i, abc[i]);
	}
	return jsNativeArray;
	//##############################################################################
	*/
}




Napi::Number functionexample::AddWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
	{
		Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
	}

	Napi::Number first = info[0].As<Napi::Number>();
	Napi::Number second = info[1].As<Napi::Number>();

	int returnValue = functionexample::add(first.Int32Value(), second.Int32Value());

	return Napi::Number::New(env, returnValue);
}



Napi::Number functionexample::myfunctionWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	functionexample::myfunction();

	char mytempbuffer[255];
	std::cin.getline(mytempbuffer, 255);
	std::cout << "your input:" << mytempbuffer << std::endl;
	return Napi::Number::New(env, true);
}

Napi::Number functionexample::SleepWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	if (info.Length() != 1 || !info[0].IsNumber())
	{
		Napi::TypeError::New(env, "Just one Number expected").ThrowAsJavaScriptException();
	}
	Napi::Number howmuchsleep = info[0].As<Napi::Number>();

	functionexample::MySleep(howmuchsleep);

	return Napi::Number::New(env, true);
}



Napi::String functionexample::HelloWrapped(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::String returnValue = Napi::String::New(env, functionexample::hello());

	return returnValue;
}

Napi::Object functionexample::Init(Napi::Env env, Napi::Object exports)
{

	//Ispress_corescWrapped
	exports.Set("IsterminateCalibration", Napi::Function::New(env, Ispress_corescWrapped));
	exports.Set("ClickMouseRight", Napi::Function::New(env, mouserightclickWrapped));
	exports.Set("ClickMouseLeft", Napi::Function::New(env, mouseleftclickWrapped));
	exports.Set("PressKeyboard", Napi::Function::New(env, keyboardpressWrapped));
	exports.Set("GetCursor", Napi::Function::New(env, GetCursorWrapped));
	exports.Set("SetCursor", Napi::Function::New(env, SetCursorWrapped));


	exports.Set("CaptureCamera", Napi::Function::New(env, capturecameraWrapped));
	exports.Set("DisConnectCamera", Napi::Function::New(env, disconnectcameraWrapped));
	exports.Set("ConnectCamera", Napi::Function::New(env, connectcameraWrapped));

	exports.Set("Sleep", Napi::Function::New(env, functionexample::SleepWrapped));
	exports.Set("myfunction", Napi::Function::New(env, functionexample::myfunctionWrapped));
	exports.Set("hello", Napi::Function::New(env, functionexample::HelloWrapped));
	exports.Set("add", Napi::Function::New(env, functionexample::AddWrapped));
	return exports;
}

///////////////////////////////
