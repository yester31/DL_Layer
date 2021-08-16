#include <io.h>
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

//파일 이름 가져오기(DFS) window용
int SearchFile(const std::string& folder_path, std::vector<std::string> &file_names, bool recursive = false)
{
	_finddata_t file_info;
	string any_file_pattern = folder_path + "\\*";
	intptr_t handle = _findfirst(any_file_pattern.c_str(), &file_info);

	if (handle == -1)
	{
		cerr << "folder path not exist: " << folder_path << endl;
		return -1;
	}

	do
	{
		string file_name = file_info.name;
		if (recursive) {
			if (file_info.attrib & _A_SUBDIR)//check whtether it is a sub direcotry or a file
			{
				if (file_name != "." && file_name != "..")
				{
					string sub_folder_path = folder_path + "//" + file_name;
					SearchFile(sub_folder_path, file_names);
					cout << "a sub_folder path: " << sub_folder_path << endl;
				}
			}
			else
			{
				string file_path = folder_path + "/" + file_name;
				file_names.push_back(file_path);
			}
		}
		else {
			if (!(file_info.attrib & _A_SUBDIR))//check whtether it is a sub direcotry or a file
			{
				string file_path = folder_path + "/" + file_name;
				file_names.push_back(file_path);
			}
		}
	} while (_findnext(handle, &file_info) == 0);
	_findclose(handle);
	return 0;
}

// linux용 
//#include <dirent.h>
//static inline int read_files_in_dir(const char *p_dir_name, std::vector<std::string> &file_names) {
//	DIR *p_dir = opendir(p_dir_name);
//	if (p_dir == nullptr) {
//		return -1;
//	}
//	struct dirent* p_file = nullptr;
//	while ((p_file = readdir(p_dir)) != nullptr) {
//		if (strcmp(p_file->d_name, ".") != 0 &&
//			strcmp(p_file->d_name, "..") != 0) {
//			std::string cur_file_name(p_file->d_name);
//			file_names.push_back(cur_file_name);
//		}
//	}
//	closedir(p_dir);
//	return 0;
//}
//std::string img_dir;
//std::vector<std::string> file_names;
//read_files_in_dir(img_dir.c_str(), file_names);


// BGR -> RGB, NHWC->NCHW, Normalize 
//void transformer(vector<uint8_t> input, string cvt, string transpose, string normalize)
//{
//	if (cvt == "BGR2RGB" || cvt == "RGB2BGR") { // CH seq change
//	
//	}
//	else if (cvt == "BGR2BGR" || cvt == "RGB2RGB") { // NO CHANAGE
//	
//	}
//	else if (cvt == "BGR2GREY" || cvt == "RGB2GRAY") {// 3CH -> 1CH
//	}
//	else { // error
//	}
//}


int main()
{
	// 0. 이미지경로 로드
	std::string img_dir = "../data";
	std::vector<std::string> file_names;
	if (SearchFile(img_dir.c_str(), file_names) < 0) {
		std::cerr << "data search error" << std::endl;
	}

	// 1. 이미지 데이터 로드
	int batch_size = 1;
	int input_width = 640;
	int input_height = 640;
	Mat img(input_height, input_width, CV_8UC3);
	Mat ori_img;
	vector<uint8_t> input(batch_size * input_height * input_width * 3);
	for (int idx = 0; idx < file_names.size(); idx++) {
		Mat ori_img = imread(file_names[idx]);
		resize(ori_img, img, img.size());
		memcpy(input.data(), img.data, batch_size * input_height * input_width * 3);
	}

	// 2. Tensor 데이터 전달(uint8_t -> float) BGR, NHWC, (0~255)
	Tensor input_t(batch_size, input_height, input_width, 3);
	for (int idx = 0; idx < input_t.getTotSize();idx++) {
		input_t.getData()[idx] = static_cast <float>(input[idx]);
	}

	// 3. BGR -> RGB, NHWC->NCHW, Normalize (-1 ~ 1)
	vector<float> output(input_t.getTotSize());
	int IN = input_t.getShape()[0];
	int IH = input_t.getShape()[1];
	int IW = input_t.getShape()[2];
	int IC = input_t.getShape()[3];
	int C_offset, H_offset, W_offset, g_in, g_out;
	int N_offset = IH * IW * IC;
	for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
		H_offset = ⁠n_idx * N_offset;
		for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++) {
			W_offset = ⁠h_idx * IW * IC + H_offset;	
			for (int w_idx = 0; w_idx < IW; w_idx++) {
				C_offset = w_idx * IC + W_offset;
				for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
					g_in = C_offset + 2 - ⁠c_idx;
					g_out = H_offset + ⁠c_idx * IH * IW + ⁠h_idx * IW + w_idx;
					output[g_out] = input_t.getData()[g_in] / 127.5f - 1.f;
				}
			}
		}
	}
	memcpy(input_t.getData(), output.data(), batch_size * input_height * input_width * 3);



	return 0;
}