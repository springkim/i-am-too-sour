#include<iostream>
#include<fstream>
#include<opencv2/opencv.hpp>
#include<vspring.h>
const char* keys = {
	"{@image |  | input image file}\
	{@variable | image_resource | variable name}\
	{@file | image.h | destination file}\
	{@width | 0 | image width}\
	{@height | 0 | image height}\
	{help h ? | | help me}\
	"};
const char* about = "Convert image to source code.";
void PrintHex(std::ostream& os, int v) {
	os.width(2);
	os.fill('0');
	os << std::hex << v;
}
int main(int argc, const char* argv[]) {
	cv::CommandLineParser parser(argc, argv, cv::String(keys));
	parser.about(about);
	if (parser.has("help") == true || parser.has("@image") == false) {
		parser.printMessage();
		return 0;
	}
	std::string arg_image = parser.get<std::string>("@image");
	std::string arg_variable = parser.get<std::string>("@variable");
	std::string arg_file = parser.get<std::string>("@file");
	int arg_width = parser.get<int>("@width");
	int arg_height = parser.get<int>("@height");

	std::cout << arg_image << std::endl;
	std::cout << arg_variable << std::endl;
	std::cout << arg_file << std::endl;
	std::cout << arg_width << std::endl;
	std::cout << arg_height << std::endl;
	
	if ((arg_variable[0] != '_' && !std::isalpha(arg_variable[0])) || std::count_if(arg_variable.begin(),arg_variable.end(),isspace)!=0) {
		std::cerr << "Wrong variable rule" << std::endl;
		return 1;
	}
	
	std::string::size_type dot = arg_image.find_last_of('.') + 1;
	std::string ext = arg_image.substr(dot, arg_image.length() - dot);
	std::transform(ext.begin(), ext.end(), ext.begin(), tolower);
	cv::Mat img;
	if (ext == "png") {
		img = cv::imread(arg_image,cv::IMREAD_UNCHANGED);
	} else {
		img = cv::imread(arg_image);
	}
	if (img.empty() == true) {
		std::cerr << "Image file not found" << std::endl;
		return 1;
	}
	if (arg_width != 0 || arg_height != 0) {
		if (img.channels() == 4) 
			for (auto it = img.begin<cv::Vec4b>(); it != img.end<cv::Vec4b>(); it++) 
				if ((*it)[3] == 0) (*it)[0] = (*it)[1] = (*it)[2] = 255;
		if(arg_width==0 && arg_height==0)
			cv::resize(img, img, cv::Size(arg_width, arg_height), 0, 0, cv::INTER_AREA);
		if (arg_width == 0 && arg_height != 0)
			cv::resize(img, img, cv::Size(img.cols*arg_height/img.rows, arg_height), 0, 0, cv::INTER_AREA);
		if (arg_width != 0 && arg_height == 0) 
			cv::resize(img, img, cv::Size(arg_width, img.rows*arg_width/img.cols), 0, 0, cv::INTER_AREA);
	}

	std::fstream fout(arg_file, std::ios::app);
	if (fout.is_open() == false) {
		std::cerr << "Unable to open file" << std::endl;
		return 1;
	}
	fout << "#if defined(_MSC_VER)" << std::endl;
	fout << "__declspec(selectany)" << std::endl;
	fout << "#elif defined(__GNUC__)" << std::endl;
	fout << "__attribute__((weak))" << std::endl;
	fout << "#endif" << std::endl;

	fout << "unsigned int " << arg_variable << "[]={" << std::endl;
	//argb
	std::ostream& iout = std::cout;
	int line = 0;
	if (img.channels() == 4) {
		for (auto it = img.begin<cv::Vec4b>(); it != img.end<cv::Vec4b>(); it++) {
			line = (line + 1) % 8;
			iout << "0x";
			if (img.channels() != 4)PrintHex(iout, 0);
			for (int c = img.channels() - 1; c >= 0; c--) {
				PrintHex(iout, (int)(*it)[c]);
			}
			if (it + 1 != img.end<cv::Vec4b>()) iout << ", ";
			if (line == 0)iout << std::endl;
		}
	}

	return 0;
}