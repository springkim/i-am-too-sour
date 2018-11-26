#ifndef NOMINMAX
#define NOMINMAX
#endif
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include<algorithm>
#include"../image.h"
HBITMAP hbitmap = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	RECT rect;
	GetClientRect(hWnd, &rect);
	switch (msg) {
		case WM_CREATE: break;
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc;
			BITMAP bitmap;
			HDC hdcMem;
			HGDIOBJ oldBitmap;
			hdc = BeginPaint(hWnd, &ps);
			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hbitmap);
			GetObject(hbitmap, sizeof(bitmap), &bitmap);
			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
		}break;
		case WM_KEYDOWN:if (wParam == VK_ESCAPE)exit(0); return TRUE;
		case WM_ERASEBKGND:return TRUE;
		case WM_DESTROY:PostQuitMessage(0); return TRUE;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
int main() {
#pragma region to_cv::Mat
	cv::Mat img = cv::Mat(cv::Size(image_empire_width,image_empire_height), CV_8UC4, image_empire);
	cv::imshow("test", img);
	cv::waitKey();
	cv::destroyAllWindows();
#pragma endregion



	wchar_t* title = L"window";
	MSG msg;
	HINSTANCE instance = GetModuleHandleA(0);
	WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, instance, LoadIcon(NULL, IDC_ICON), LoadCursor(NULL, IDC_ARROW), WHITE_BRUSH, NULL,title };
	RegisterClass(&wndClass);
	unsigned int caption_height = 39;
	unsigned int caption_width = 300;
	HWND hwnd = CreateWindow(title, title, WS_OVERLAPPEDWINDOW, 0, 0, std::max(caption_width, image_empire_width), image_empire_height + caption_height, NULL, NULL, instance, NULL);
#pragma region to_HBITMAP
	//https://docs.microsoft.com/en-us/windows/desktop/directshow/top-down-vs--bottom-up-dibs
	BITMAPINFOHEADER   bmih;
	memset(&bmih, 0, sizeof(BITMAPINFOHEADER));
	bmih.biWidth = image_empire_width;
	bmih.biHeight = -image_empire_height;
	bmih.biBitCount = 32;
	bmih.biCompression = BI_RGB;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biPlanes = 1;
	BITMAPINFO* bmi = (BITMAPINFO*)&bmih;
	HDC hdc = GetDC(hwnd);
	hbitmap = CreateDIBitmap(hdc, &bmih, CBM_INIT, image_empire, bmi, DIB_RGB_COLORS);
#pragma endregion


	ShowWindow(hwnd, 1);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DeleteObject(hbitmap);
	ReleaseDC(hwnd, hdc);

	return 0;
}