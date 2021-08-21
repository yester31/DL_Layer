// 2021-8-05 by YH PARK // 검증 필요

/***************************************************************************
	FullyConnected algotirhm
****************************************************************************/
#include "Tensor.h"

void fullyConnected(vector<float>& Output, vector<float>& Input, vector<float>& Weight, int out_features, int input_n, int input_c, int input_h, int input_w) {

	int in_features = input_c * input_h * input_w;
	for (int n_idx = 0; n_idx < input_n; n_idx++)
	{
		int temp2i = n_idx * in_features;
		int temp2o = n_idx * out_features;
		for (int f_idx = 0; f_idx < out_features; f_idx++)
		{
			float sum = 0;
			int g_idx_o = f_idx + temp2o;
			int temp2k = f_idx * in_features;
			for (int ⁠c_idx = 0; ⁠c_idx < input_c; ⁠c_idx++)
			{
				int temp3i = ⁠c_idx * input_h * input_w + temp2i;
				int temp3k = ⁠c_idx * input_h * input_w + temp2k;
				for (int ⁠h_idx = 0; ⁠h_idx < input_h; ⁠h_idx++)
				{
					int temp4i = ⁠h_idx * input_w + temp3i;
					int temp4k = ⁠h_idx * input_w + temp3k;
					for (int w_idx = 0; w_idx < input_w; w_idx++)
					{
						int ⁠g_idx_i = w_idx + temp4i;
						int g_idx_k = w_idx + temp4k;
						sum += Input[⁠g_idx_i] * Weight[g_idx_k];
					}
				}
			}
			Output[g_idx_o] = sum;
		}
	}
}


//int fc_test()
//{
//	int IN = 2;
//	int IC = 2;
//	int IH = 4;
//	int IW = 4;
//
//	int OF = 3;
//
//	// weight[OC][lC][KH][KW] 
//	// 임시 weight 값 
//	vector<float> weight(OF * IC * IH * IW);
//	initTensor(weight);
//	valueCheck(weight, OF, IC, IH, IW, 1);
//
//	// d[IN][IC][IH][IW] 
//	// 임시 input 값 
//	vector<float> input(IN * IC * IH * IW);
//	initTensor(input);
//	valueCheck(input, IN, IC, IH, IW, 1);
//
//
//
//	return 0;
//}