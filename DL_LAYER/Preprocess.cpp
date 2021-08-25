// 2021-8-25 by YH PARK

/***************************************************************************
	Preprocess algotirhm (without any option)
****************************************************************************/
#include "Tensor.h"

void Preprocess(std::vector<float> &output, std::vector<uint8_t> &input, int BatchSize, int channels, int height, int width, std::vector<float> mean, std::vector<float> std)
{
	//std::vector<float> mean = { 0.485, 0.456, 0.406 }, std::vector<float> std = { 0.229, 0.224, 0.225 }
	// INPUT  = BGR[NHWC](0, 255)
	// OUTPUT  = RGB[NCHW](0.f,1.f)
	// This equation include 3 steps
	// 1. Scale Image to range [0.f, 1.0f], /255
	// 2. Normalize Image using per channel Mean and per channel Standard Deviation, (mean=(0.485, 0.456, 0.406), std=(0.229, 0.224, 0.225)RGB)
	// 3. Shuffle HWC to CHW form
	// 4. BGR -> RGB
	int offset = channels * height * width;
	int b_off, c_off, h_off, h_off_o, w_off_o;
	for (int b = 0; b < BatchSize; b++)
	{
		b_off = b * offset;
		for (int c = 0; c < channels; c++)
		{
			c_off = c * height * width + b_off;
			for (int h = 0; h < height; h++)
			{
				h_off = h * width + c_off;
				h_off_o = h * width * channels + b_off;
				for (int w = 0; w < width; w++)
				{
					int dstIdx = h_off + w;
					int srcIdx = h_off_o + w * channels + 2 - c;
					output[dstIdx] = (static_cast<const float>(input[srcIdx]) / 255.f - mean[2 - c]) / std[2 - c];
				}
			}
		}
	}
};

void Preprocess(std::vector<float> &output, std::vector<uint8_t>& input, int BatchSize, int channels, int height, int width)
{
	// INPUT  = BGR[NHWC](0, 255)
	// OUTPUT = RGB[NCHW](0.f,1.f)
	// This equation include 3 steps
	// 1. Scale Image to range [0.f, 1.0f], /255
	// 2. Shuffle HWC to CHW form
	// 3. BGR -> RGB
	int offset = channels * height * width;
	int b_off, c_off, h_off, h_off_o, w_off_o;
	for (int b = 0; b < BatchSize; b++)
	{
		b_off = b * offset;
		for (int c = 0; c < channels; c++)
		{
			c_off = c * height * width + b_off;
			for (int h = 0; h < height; h++)
			{
				h_off = h * width + c_off;
				h_off_o = h * width * channels + b_off;
				for (int w = 0; w < width; w++)
				{
					int dstIdx = h_off + w;
					int srcIdx = h_off_o + w * channels + 2 - c;
					output[dstIdx] = (static_cast<const float>(input[srcIdx]) / 255.f );
				}
			}
		}
	}
};

int main()
{
	int IN = 2;
	int IC = 3;
	int IH = 4;
	int IW = 4;

	std::vector<float> mean = { 0.485, 0.456, 0.406 };
	std::vector<float> std = { 0.229, 0.224, 0.225 };

	// input[IN1][IH][IW][IC]
	vector<uint8_t> input(IN * IC * IH * IW);
	scalarTensor_b(input.data(), IN,  IH, IW, IC, 0, 1);
	valueCheck_b(input, IN, IH, IW, IC);

	vector<float> output(IN * IC * IH * IW);

	long long start_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

	Preprocess(output, input, IN, IC, IH, IW);
	//Preprocess(output, input, IN, IC, IH, IW, mean, std);
	valueCheck_b(output, IN, IC, IH, IW);

	long long end_usec3 = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	int frame_sec3 = int(end_usec3 - start_usec3);

	std::cout << "======================================================" << std::endl;
	std::cout << "dur time :: " << frame_sec3 << "micro sec" << std::endl;
	//tofile_b(output, "../Calc_Validation/output/C_Tensor_preprocess");
	tofile_b(output, "../Calc_Validation/output/C_Tensor_preprocess2");
}