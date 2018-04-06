﻿/*
// Copyright (c) 2016 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#pragma once

#include "kernel_base.h"
#include "kernel_selector_common.h"
#include "kernel_selector_params.h"
#include "kernel_runner_interface.h"
#include "auto_tuner.h"

namespace KernelSelector 
{
    using KernelList = std::vector<std::shared_ptr<KernelBase>>;
    using ForceList = std::map<std::string, bool>;

    class KernelSelctorBase
    {
    public:
        KernelSelctorBase();
        virtual ~KernelSelctorBase() {}

        virtual KernelsData GetBestKernels(const Params& params, const OptionalParams& options) const = 0;

    protected:
        template<typename T>
        inline void Attach()
        {
            implementations.push_back(std::make_shared<T>(T()));
        }

        virtual KernelsData GetNaiveBestKernel(const Params& params, const OptionalParams& options, KernelType kType) const;

        virtual KernelsData GetAutoTuneBestKernel(const Params& params, const OptionalParams& options, KernelType kType) const;

        KernelList implementations;
        ForceList forceKernels;

        static AutoTuner autoTuner;
    };
}