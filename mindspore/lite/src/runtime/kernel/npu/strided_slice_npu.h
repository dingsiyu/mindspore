/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_NPU_STRIDEDSLICE_NPU_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_NPU_STRIDEDSLICE_NPU_H_
#include <vector>
#include "src/ops/strided_slice.h"
#include "nnacl/strided_slice.h"
#include "src/runtime/kernel/npu/npu_kernel.h"
#include "include/graph/op/all_ops.h"
namespace mindspore::kernel {
class StridedSliceNPUKernel : public NPUKernel {
 public:
  StridedSliceNPUKernel(OpParameter *parameter, const std::vector<lite::Tensor *> &inputs,
                        const std::vector<lite::Tensor *> &outputs, const lite::InnerContext *ctx,
                        const mindspore::lite::PrimitiveC *primitive)
      : NPUKernel(parameter, inputs, outputs, ctx, primitive) {
    auto strided_slice = reinterpret_cast<const mindspore::lite::StridedSlice *>(primitive);
    begin_mask_ = strided_slice->GetBeginMask();
    end_mask_ = strided_slice->GetEndMask();
    ellipsis_mask_ = strided_slice->GetEllipsisMask();
    new_axis_mask_ = strided_slice->GetNewAxisMask();
    shrink_axis_mask_ = strided_slice->GetShrinkAxisMask();
  }
  ~StridedSliceNPUKernel() override;

  int IsSupport(const std::vector<lite::Tensor *> &inputs, const std::vector<lite::Tensor *> &outputs,
                OpParameter *opParameter) override;
  int SetNPUInputs(const std::vector<lite::Tensor *> &inputs, const std::vector<lite::Tensor *> &outputs,
                   const std::vector<ge::Operator *> &npu_inputs) override;
  ge::Operator *GetNPUOp() override;

 private:
  hiai::op::StridedSlice *op_ = nullptr;
  int begin_mask_;
  int end_mask_;
  int ellipsis_mask_;
  int new_axis_mask_;
  int shrink_axis_mask_;
};
}  // namespace mindspore::kernel
#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_NPU_STRIDEDSLICE_NPU_H_