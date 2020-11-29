/*
 * Copyright (C) 2020 Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */

#include "close_event.h"

namespace kraken::binding::jsc {

void bindCloseEvent(std::unique_ptr<JSContext> &context) {
  auto event = JSCloseEvent::instance(context.get());
  JSC_GLOBAL_SET_PROPERTY(context, "CloseEvent", event->classObject);
};

JSCloseEvent *JSCloseEvent::instance(JSContext *context) {
  static std::unordered_map<JSContext *, JSCloseEvent *> instanceMap{};
  if (!instanceMap.contains(context)) {
    instanceMap[context] = new JSCloseEvent(context);
  }
  return instanceMap[context];
}

JSCloseEvent::JSCloseEvent(JSContext *context) : JSEvent(context, "CloseEvent") {}

JSObjectRef JSCloseEvent::instanceConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount,
                                              const JSValueRef *arguments, JSValueRef *exception) {
  if (argumentCount != 1) {
    JSC_THROW_ERROR(ctx, "Failed to construct 'JSCloseEvent': 1 argument required, but only 0 present.", exception);
    return nullptr;
  }

  JSStringRef dataStringRef = JSValueToStringCopy(ctx, arguments[0], exception);
  auto event = new CloseEventInstance(this, dataStringRef);
  return event->object;
}

JSValueRef JSCloseEvent::getProperty(std::string &name, JSValueRef *exception) {
  return nullptr;
}

CloseEventInstance::CloseEventInstance(JSCloseEvent *jsCloseEvent, NativeCloseEvent *nativeCloseEvent)
  : EventInstance(jsCloseEvent, nativeCloseEvent->nativeEvent), nativeCloseEvent(nativeCloseEvent) {
  code = nativeCloseEvent->code;
  m_reason.setString(nativeCloseEvent->reason);
  wasClean = nativeCloseEvent->wasClean == 1;
}

CloseEventInstance::CloseEventInstance(JSCloseEvent *jsCloseEvent, JSStringRef data)
  : EventInstance(jsCloseEvent, "close") {
  nativeCloseEvent = new NativeCloseEvent(nativeEvent);
}

JSValueRef CloseEventInstance::getProperty(std::string &name, JSValueRef *exception) {
  auto propertyMap = JSCloseEvent::getCloseEventPropertyMap();

  if (!propertyMap.contains(name)) return EventInstance::getProperty(name, exception);

  auto property = propertyMap[name];
  switch(property) {
  case JSCloseEvent::CloseEventProperty::kCode:
    return JSValueMakeNumber(ctx, code);
  case JSCloseEvent::CloseEventProperty::kReason:
    return m_reason.makeString();
  case JSCloseEvent::CloseEventProperty::kWasClean:
    return JSValueMakeBoolean(ctx, wasClean);
  }

  return nullptr;
}

void CloseEventInstance::setProperty(std::string &name, JSValueRef value, JSValueRef *exception) {
  auto propertyMap = JSCloseEvent::getCloseEventPropertyMap();
  if (propertyMap.contains(name)) {
    auto property = propertyMap[name];

    switch (property) {

    case JSCloseEvent::CloseEventProperty::kCode: {
      code = JSValueToNumber(ctx, value, exception);
      break;
    }
    case JSCloseEvent::CloseEventProperty::kReason: {
      JSStringRef str = JSValueToStringCopy(ctx, value, exception);
      m_reason.setString(str);
      break;
    }
    case JSCloseEvent::CloseEventProperty::kWasClean: {
      wasClean = JSValueToBoolean(ctx, value);
      break;
    }
    }
  } else {
    EventInstance::setProperty(name, value, exception);
  }
}

CloseEventInstance::~CloseEventInstance() {
  nativeCloseEvent->reason->free();
  delete nativeCloseEvent;
}

void CloseEventInstance::getPropertyNames(JSPropertyNameAccumulatorRef accumulator) {
  EventInstance::getPropertyNames(accumulator);

  for (auto &property : JSCloseEvent::getCloseEventPropertyNames()) {
    JSPropertyNameAccumulatorAddName(accumulator, property);
  }
}

std::vector<JSStringRef> &JSCloseEvent::getCloseEventPropertyNames() {
  static std::vector<JSStringRef> propertyNames{JSStringCreateWithUTF8CString("code"),
                                                JSStringCreateWithUTF8CString("reason"),
                                                JSStringCreateWithUTF8CString("wasClean")};
  return propertyNames;
}

const std::unordered_map<std::string, JSCloseEvent::CloseEventProperty> &JSCloseEvent::getCloseEventPropertyMap() {
  static std::unordered_map<std::string, CloseEventProperty> propertyMap{{"code", CloseEventProperty::kCode},
                                                                         {"reason", CloseEventProperty::kReason},
                                                                         {"wasClean", CloseEventProperty::kWasClean}};
  return propertyMap;
}
} // namespace kraken::binding::jsc
