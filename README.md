DL_Layer
=============
딥러닝 프레임워크 만들기

아키텍쳐 설계
------------
계획중
model <- network <- layer <- tensor
run(forward, backward)

기능
------------
### forward layer 완성
- Conventional_Conv2d
- Zero_Padding
- Pool2d (Avg, Max)
- Eltwise (Prod, Sum)
- Activation (Tan, Sigmoid, ReLU, Swish, reakyReLU) 검증필요
- Dense(fullyconnected) 검증필요
- Softmax 검증필요

### forward layer 예정
- GlobalAvgPooling
- Concat
- BatchNorm
- DeConvolution
- Transformer(bgr->rgb, nhwc->nchw, resize?)
- DataLoader

### 추후 예정
- backward
- winograd, gemm, strassen Convolution 도입
- openmp 적용

검증
-------------
Calc_Validation   
torch 1.9.0+cu111 버전을 이용하여 계산 결과값 비교
