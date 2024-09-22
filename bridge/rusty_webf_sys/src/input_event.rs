/*
* Copyright (C) 2022-present The WebF authors. All rights reserved.
*/
use std::ffi::*;
use crate::*;
#[repr(C)]
pub struct InputEventRustMethods {
  pub version: c_double,
  pub input_type: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
  pub data: extern "C" fn(ptr: *const OpaquePtr) -> *const c_char,
}
pub struct InputEvent {
  pub ptr: *const OpaquePtr,
  context: *const ExecutingContext,
  method_pointer: *const InputEventRustMethods,
}
impl InputEvent {
  pub fn initialize(ptr: *const OpaquePtr, context: *const ExecutingContext, method_pointer: *const InputEventRustMethods) -> InputEvent {
    InputEvent {
      ptr,
      context,
      method_pointer,
    }
  }
  pub fn ptr(&self) -> *const OpaquePtr {
    self.ptr
  }
  pub fn context<'a>(&self) -> &'a ExecutingContext {
    assert!(!self.context.is_null(), "Context PTR must not be null");
    unsafe { &*self.context }
  }
  pub fn input_type(&self) -> String {
    let value = unsafe {
      ((*self.method_pointer).input_type)(self.ptr)
    };
    let value = unsafe { std::ffi::CStr::from_ptr(value) };
    let value = value.to_str().unwrap();
    value.to_string()
  }
  pub fn data(&self) -> String {
    let value = unsafe {
      ((*self.method_pointer).data)(self.ptr)
    };
    let value = unsafe { std::ffi::CStr::from_ptr(value) };
    let value = value.to_str().unwrap();
    value.to_string()
  }
}