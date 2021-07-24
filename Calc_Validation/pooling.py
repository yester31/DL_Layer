import torch # torch 1.9.0+cu111
import numpy as np
from compare import *

IN = 2
IC = 2
IH = 4
IW = 4
PW = 3
PS = 1

input_np = np.arange(1, IN * IC * IH * IW + 1).reshape(IN, IC, IH, IW)
input = torch.from_numpy(input_np).type(torch.FloatTensor)
print(input)

#pooling = torch.nn.AvgPool2d((PW, PW), stride=(PS, PS)) # avg pooling 사용시
pooling = torch.nn.MaxPool2d((PW, PW), stride=(PS, PS)) # max pooling 사용시

output = pooling(input)
print(output)

#output_c = np.fromfile("../output/C_Tensor_avg_p", dtype=np.float32)
output_c = np.fromfile("../output/C_Tensor_max_p", dtype=np.float32)
output_py = output.detach().numpy().flatten()

compare_two_tensor(output_py, output_c)