import torch # torch 1.9.0+cu111
import numpy as np
from compare import *

input_np = np.arange(1, 11)
input = torch.from_numpy(input_np).type(torch.FloatTensor)
print(input)

sigmoid = torch.nn.Sigmoid()
tanh = torch.nn.Tanh()
relu = torch.nn.ReLU()
silu = torch.nn.SiLU()
leakyrelu = torch.nn.LeakyReLU()

output = leakyrelu(input)
print(output)

#output_c = np.fromfile("output/C_Tensor_A_Sigmoid", dtype=np.float32)
#output_c = np.fromfile("output/C_Tensor_A_Tanh", dtype=np.float32)
#output_c = np.fromfile("output/C_Tensor_A_ReLU", dtype=np.float32)
#output_c = np.fromfile("output/C_Tensor_A_Swish", dtype=np.float32)
output_c = np.fromfile("output/C_Tensor_A_LeakRelu", dtype=np.float32)

output_py = output.detach().numpy().flatten()

compare_two_tensor(output_py, output_c)