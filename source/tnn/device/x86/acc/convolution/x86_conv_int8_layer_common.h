// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef TNN_SOURCE_TNN_DEVICE_X86_X86_CONV_INT8_LAYER_ACC_COMMON_H_
#define TNN_SOURCE_TNN_DEVICE_X86_X86_CONV_INT8_LAYER_ACC_COMMON_H_

#include "tnn/device/x86/acc/x86_layer_acc.h"

#ifndef SIMD_INT8CONV_TILE_HW
#define SIMD_INT8CONV_TILE_HW (4)
#endif

namespace TNN_NS {

// @brief conv layer cpu acc

class X86ConvInt8LayerCommon : public X86LayerAcc {
public:
    virtual ~X86ConvInt8LayerCommon();

    Status Init(Context *context, LayerParam *param, LayerResource *resource, const std::vector<Blob *> &inputs,
                const std::vector<Blob *> &outputs);
                
    virtual Status DoForward(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs);

    static bool isPrefered(ConvLayerParam *param, const std::vector<Blob *> &inputs,
                           const std::vector<Blob *> &outputs);

    virtual Status allocateBufferWeight(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs);

    virtual Status allocateBufferBias(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs);

    virtual Status allocateBufferScale(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs);

    virtual Status allocateBufferAddScale(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs);

    virtual Status setFusionParam(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs);

protected:
    RawBuffer buffer_weight_;
    RawBuffer buffer_im2col_;
    RawBuffer buffer_bias_;
    RawBuffer buffer_scale_;
    RawBuffer buffer_add_scale_;
    // for conv relu6 fusion
    RawBuffer relu6_max_;

    long relu_ = 0;
    int tile_blk_ = 32;

    std::function<void(int8_t *, const int8_t *, const ConvLayerParam *, size_t, size_t, int,
                       DimsVector, DimsVector)> im_col_func_;
};

}  // namespace TNN_NS

#endif  // TNN_SOURCE_TNN_DEVICE_X86_X86_CONV_INT8_LAYER_ACC_COMMON_H_
