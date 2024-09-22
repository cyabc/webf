/*
* Copyright (C) 2022-present The WebF authors. All rights reserved.
*/
use std::ffi::*;
use crate::*;
#[repr(C)]
pub struct MouseEventRustMethods {
  pub version: c_double,
  pub client_x: extern "C" fn(ptr: *const OpaquePtr) -> f64,
  pub client_y: extern "C" fn(ptr: *const OpaquePtr) -> f64,
  pub offset_x: extern "C" fn(ptr: *const OpaquePtr) -> f64,
  pub offset_y: extern "C" fn(ptr: *const OpaquePtr) -> f64,
}
pub struct MouseEvent {
  pub ptr: *const OpaquePtr,
  context: *const ExecutingContext,
  method_pointer: *const MouseEventRustMethods,
}
impl MouseEvent {
  pub fn initialize(ptr: *const OpaquePtr, context: *const ExecutingContext, method_pointer: *const MouseEventRustMethods) -> MouseEvent {
    MouseEvent {
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
  pub fn client_x(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).client_x)(self.ptr)
    };
    value
  }
  pub fn client_y(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).client_y)(self.ptr)
    };
    value
  }
  pub fn offset_x(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).offset_x)(self.ptr)
    };
    value
  }
  pub fn offset_y(&self) -> f64 {
    let value = unsafe {
      ((*self.method_pointer).offset_y)(self.ptr)
    };
    value
  }
}