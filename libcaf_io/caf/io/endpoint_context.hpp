/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright (C) 2011 - 2016                                                  *
 * Dominik Charousset <dominik.charousset (at) haw-hamburg.de>                *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#ifndef CAF_IO_ENDPOINT_CONTEXT_HPP
#define CAF_IO_ENDPOINT_CONTEXT_HPP

#include <unordered_map>

#include "caf/variant.hpp"
#include "caf/response_promise.hpp"

#include "caf/io/dgram_handle.hpp"
#include "caf/io/connection_handle.hpp"

#include "caf/io/basp/header.hpp"
#include "caf/io/basp/connection_state.hpp"

namespace caf {
namespace io {

// stores meta information for active endpoints
struct endpoint_context {
  // denotes what message we expect from the remote node next
  basp::connection_state cstate;
  // our currently processed BASP header
  basp::header hdr;
  // the handle for I/O operations
  variant<connection_handle, dgram_handle> hdl;
  // network-agnostic node identifier
  node_id id;
  // port
  uint16_t remote_port;
  // pending operations to be performed after handshake completed
  optional<response_promise> callback;
  // TODO: introduce some call to ask scribe for such info
  // Should be configurable by policies in the future
  bool requires_ordering;
  uint16_t seq_incoming;
  uint16_t seq_outgoing;
  std::unordered_map<uint16_t, std::pair<basp::header,std::vector<char>>> pending;
};

} // namespace io
} // namespace caf

#endif // CAF_IO_ENDPOINT_CONTEXT_HPP
