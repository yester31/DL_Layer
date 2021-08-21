#pragma once
#include "Tensor.h"

class Layer
{
public:

	Layer()
	{}

	Layer(Layer &layer)
	{
		*this = layer;
	}

	virtual Tensor calculate(Tensor output, Tensor input);
	virtual void initWeight();
	~Layer() {}

public:
	Tensor weight;
	string name;

};

class ConvolutionLayer : public Layer {
public:

	ConvolutionLayer(ConvolutionLayer &layer)
	{
		*this = layer;
	}

	ConvolutionLayer(int C, int K, int KH, int KW, int Stride, bool bias = false) 
		: C(C), K(K), KH(KH), KW(KW), stride(Stride)
	{
		name = "Convolution Layer";
		initWeight();
	}

	Tensor calculate(Tensor output, Tensor input)
	{
		// 1. weight tensor 
		float* weight_data = weight.getData();

		// 2. input tensor  
		float* input_data = input.getData();
		int IN = input.getShape()[0];
		int IC = input.getShape()[1];
		int IH = input.getShape()[2];
		int IW = input.getShape()[3];

		// 3. output tenosr 재설정
		int OH = ((IH - KH) / stride) + 1;
		int OW = ((IW - KW) / stride) + 1;
		output.reConstruct(IN, K, OH, OW);
		float* output_data = output.getData();

		// 4. 연산 수행 
		std::cout << "===== Convolution ===== \n" << std::endl;

		int C_offset_i, C_offset_o, C_offset_k, H_offset_i, H_offset_o, H_offset_k, W_offset_i, W_offset_o, W_offset_k, ⁠g_idx_i, g_idx_o, g_idx_k;
		int N_offset_i = IC * IH * IW;
		int N_offset_o = K * OH * OW;
		int N_offset_k = IC * KH * KW;
		for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
			C_offset_i = ⁠n_idx * N_offset_i;
			C_offset_o = ⁠n_idx * N_offset_o;
			for (int k_idx = 0; k_idx < K; k_idx++) {
				C_offset_k = k_idx * N_offset_k;
				H_offset_o = k_idx * OH * OW + C_offset_o;
				for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
					H_offset_i = ⁠c_idx * IH * IW + C_offset_i;
					H_offset_k = ⁠c_idx * KH * KW + C_offset_k;
					for (int rowStride = 0; rowStride < OH; rowStride++) {
						W_offset_o = rowStride * OW + H_offset_o;
						for (int colStride = 0; colStride < OW; colStride++) {
							float sum = 0;
							g_idx_o = colStride + W_offset_o;
							for (int y = rowStride * stride; y < rowStride * stride + KH; y++) {
								W_offset_i = y * IW + H_offset_i;
								W_offset_k = (y - rowStride * stride) * KH + H_offset_k;
								for (int x = colStride * stride; x < colStride * stride + KW; x++) {
									⁠g_idx_i = x + W_offset_i;
									g_idx_k = (x - colStride * stride) + W_offset_k;
									sum += input_data[⁠g_idx_i] * weight_data[g_idx_k];
								}
							}
							output_data[g_idx_o] += sum;
						}
					}
				}
			}
		}	
	}

	// kaiming HE Uniform initialization
	void initWeight()
	{
		vector<int> weightShape{K, C, KH, KW};
		weight.setShape(weightShape);
		float min = -sqrt(5);
		float max = sqrt(5);
		mt19937 random((random_device()()));
		uniform_real_distribution<float> dist(min, max);

		std::cout << "===== Init Weight (kaiming HE Uniform) =====" << std::endl;
		for (int i = 0; i < weight.getTotSize(); i++) {
			weight.getData()[i] = dist(random);
		}
	}

public:
	int KH;
	int KW;
	int stride;
	int K;
	int C;
};