import torch # torch 1.9.0+cu111
import numpy as np
from compare import *

IN = 2
IC = 3
IH = 4
IW = 4

mean = np.array([ 0.485, 0.456, 0.406])
std = np.array([ 0.229, 0.224, 0.225 ])

input_np = np.arange(0, IN * IC * IH * IW ).reshape(IN, IH, IW, IC) #[N,H,W,C]
input = input_np.astype(np.uint8)
print(input)
input = input.astype(np.float32)    # uint -> float32
input /= 255.                       # [0.f, 1.0f], /255
#input = (input - mean)/ std         # Normalize
input = input[:,:,:,::-1]           # bgr -> rgb
output_py = np.transpose(input,(0,3,1,2)) # nhwc -> nchw
print(output_py.reshape(IN, IC, IH, IW))

output_c = np.fromfile("../Calc_Validation/output/C_Tensor_preprocess2", dtype=np.float32)

compare_two_tensor(output_py.flatten(), output_c)
