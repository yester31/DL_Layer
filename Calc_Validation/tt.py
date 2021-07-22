import torch # v1.8.0
import numpy as np

OC = 1
IN = 1
IC = 1
IH = 4
IW = 4
KH = 3
KW = 3

weight = torch.ones([OC, IC, KH, KW], dtype=torch.float32, requires_grad=False)
print(weight)

input_np = np.arange(1, IN * IC * IH * IW + 1).reshape(IN, IC, IH, IW)
input = torch.from_numpy(input_np).type(torch.FloatTensor)
print(input)

conservertive_convolution = torch.nn.Conv2d(IC, OC, (KH, KH), stride=(1, 1), bias=False)
conservertive_convolution.weight = torch.nn.Parameter(weight)

output = conservertive_convolution(input)
print(output)