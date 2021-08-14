#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // for setw()
#include <fstream>
using namespace std;

template <typename T>
class Tensor
{
public:

	Tensor() : totSize(0)
	{}

	Tensor(int size) : totSize (size)
	{
		shape = { size };
		data.resize(size);
	}

	Tensor(int N, int C, int H, int W) : totSize (N * C * H * W)
	{
		shape = { N,C,H,W };
		data.resize(N * C * H * W);
	}

	void initStep(T start = 1, T step = 0)
	{
		std::cout << "===== InitTensor func (step)=====" << std::endl;
		T count = start;
		for (int i = 0; i < data.size(); i++) {
			data[i] = count;
			count += step;
		}
	}

	void initScalar(T scalar = 0)
	{
		std::cout << "===== InitTensor func (scalar = " << scalar << ")=====" << std::endl;
		for (int i = 0; i < data.size(); i++) {
			data[i] = scalar;
		}
	}

	void initRandom(T min = -10.f, T max = 10.f)
	{
		std::cout << "===== InitTensor func (random) =====" << std::endl;
		for (int i = 0; i < data.size(); i++) {
			data[i] = min + static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / (max - min)));
		}
	}

	void setName(string name) {
		*this.name = name;
	}

	void valueCheck() {
		std::cout << "===== valueCheck func =====" << std::endl;
		int IN,	IC, IH, IW;
		if (shape.size() == 4) {
			IN = shape[0];
			IC = shape[1];
			IH = shape[2];
			IW = shape[3];
		}
		else if(shape.size() == 1){
			IN = shape[0];
			IC = 0;
			IH = 0;
			IW = 0;
		}
		else {
			return;
		}

		int N_offset = IC * IH * IW;
		int C_offset, H_offset, W_offset, g_idx;
		for (int ⁠n_idx = 0; ⁠n_idx < IN; ⁠n_idx++) {
			C_offset = ⁠n_idx * N_offset;
			for (int ⁠c_idx = 0; ⁠c_idx < IC; ⁠c_idx++) {
				H_offset = ⁠c_idx * IW * IH + C_offset;
				for (int ⁠h_idx = 0; ⁠h_idx < IH; ⁠h_idx++) {
					W_offset = ⁠h_idx * IW + H_offset;
					for (int w_idx = 0; w_idx < IW; w_idx++) {
						g_idx = w_idx + W_offset;
						std::cout << setw(5) << data[g_idx] << " ";
					}std::cout << std::endl;
				}std::cout << std::endl; std::cout << std::endl;
			}
		}
	}

	vector<int> shape;
	string name;
	vector<T> data;
	int totSize;
};


int main()
{
	int N = 1;
	int C = 2;
	int H = 3;
	int W = 4;

	Tensor<float> t1(N, C, H, W);

	t1.initStep();
	t1.valueCheck();
	

	return 0;
}