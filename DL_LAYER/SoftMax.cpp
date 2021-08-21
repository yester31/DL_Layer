// 2021-8-05 by YH PARK // 검증 필요

/***************************************************************************
	FullyConnected algotirhm
****************************************************************************/
#include "Tensor.h"

void softMax(vector<float>& softMaxOutput, vector<float>& softMaxInput, int input_n, int lastNodeNumber)
{
	for (int n_idx = 0; n_idx < input_n; n_idx++) { // batch
		float sum = 0.0;
		for (int i = 0; i < lastNodeNumber; i++)
		{
			int ⁠g_idx_i = n_idx * lastNodeNumber + i;
			sum += exp(softMaxInput[⁠g_idx_i]);
		}
		for (int i = 0; i < lastNodeNumber; i++)
		{
			int ⁠g_idx_o = n_idx * lastNodeNumber + i;
			softMaxOutput[⁠g_idx_o] = exp(softMaxInput[⁠g_idx_o]) / sum;
		}
	}
}