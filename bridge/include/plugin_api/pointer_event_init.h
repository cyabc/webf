// Generated by WebF TSDL, don't edit this file directly.
// Generate command: node scripts/generate_binding_code.js
// clang-format off
/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */
#ifndef WEBF_CORE_WEBF_API_PLUGIN_API_POINTER_EVENT_INIT_H_
#define WEBF_CORE_WEBF_API_PLUGIN_API_POINTER_EVENT_INIT_H_
#include <stdint.h>
#include "webf_value.h"
namespace webf {
struct WebFPointerEventInit {
  int32_t is_primary;
  double pointer_id;
  const char* pointer_type;
  double pressure;
  double tangential_pressure;
  double tilt_x;
  double tilt_y;
  double twist;
  double width;
  double height;
};
}  // namespace webf
#endif  // WEBF_CORE_WEBF_API_PLUGIN_API_POINTER_EVENT_INIT_H_