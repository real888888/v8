// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_RUNTIME_PROFILER_H_
#define V8_RUNTIME_PROFILER_H_

#include "src/allocation.h"

namespace v8 {
namespace internal {

class Isolate;
class JSFunction;

class RuntimeProfiler {
 public:
  explicit RuntimeProfiler(Isolate* isolate);

  void MarkCandidatesForOptimization();

  void NotifyICChanged() { any_ic_changed_ = true; }

  void AttemptOnStackReplacement(JSFunction* function, int nesting_levels = 1);

 private:
  void MaybeOptimizeFullCodegen(JSFunction* function, int frame_count,
                                bool frame_optimized);
  void MaybeOptimizeIgnition(JSFunction* function);
  void Optimize(JSFunction* function, const char* reason);
  void Baseline(JSFunction* function, const char* reason);

  bool CodeSizeOKForOSR(Code* shared_code);

  Isolate* isolate_;

  bool any_ic_changed_;
};

}  // namespace internal
}  // namespace v8

#endif  // V8_RUNTIME_PROFILER_H_
