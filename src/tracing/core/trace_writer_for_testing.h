/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SRC_TRACING_CORE_TRACE_WRITER_FOR_TESTING_H_
#define SRC_TRACING_CORE_TRACE_WRITER_FOR_TESTING_H_

#include "perfetto/protozero/message_handle.h"
#include "perfetto/trace/trace_packet.pb.h"
#include "perfetto/tracing/core/trace_writer.h"
#include "src/protozero/scattered_stream_delegate_for_testing.h"

namespace perfetto {

// A specialization of TraceWriter for testing which writes into memory
// allocated by the ScatteredStreamDelegateForTesting.
// See //include/perfetto/tracing/core/trace_writer.h for docs.
class TraceWriterForTesting : public TraceWriter {
 public:
  // TraceWriterForTesting(const ScatteredStreamDelegateForTesting& delegate);
  TraceWriterForTesting();
  ~TraceWriterForTesting() override;

  // TraceWriter implementation. See documentation in trace_writer.h.
  // TracePacketHandle is defined in trace_writer.h
  TracePacketHandle NewTracePacket() override;
  void Flush(std::function<void()> callback = {}) override;

  std::unique_ptr<protos::TracePacket> ParseProto();

  WriterID writer_id() const override;

 private:
  TraceWriterForTesting(const TraceWriterForTesting&) = delete;
  TraceWriterForTesting& operator=(const TraceWriterForTesting&) = delete;

  ScatteredStreamDelegateForTesting delegate_;
  protozero::ScatteredStreamWriter stream_;

  // The packet returned via NewTracePacket(). Its owned by this class,
  // TracePacketHandle has just a pointer to it.
  std::unique_ptr<protos::pbzero::TracePacket> cur_packet_;
};

}  // namespace perfetto

#endif  // SRC_TRACING_CORE_TRACE_WRITER_FOR_TESTING_H_
