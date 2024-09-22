/*
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */

#include "plugin_api/<%= blob.filename.replace('plugin_api_', '') %>.h"
#include "plugin_api/event_target.h"
#include "plugin_api/exception_state.h"
#include "core/dom/events/event.h"
#include "core/dom/events/event_target.h"
#include "core/events/animation_event.h"
#include "core/events/close_event.h"
#include "core/events/focus_event.h"
#include "core/events/gesture_event.h"
#include "core/events/hashchange_event.h"
#include "core/events/input_event.h"
#include "core/events/intersection_change_event.h"
#include "core/events/mouse_event.h"
#include "core/events/pointer_event.h"
#include "core/events/transition_event.h"
#include "core/events/ui_event.h"

<%= content %>
