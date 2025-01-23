use std::ffi::c_void;
use webf_sys::executing_context::ExecutingContextRustMethods;
use webf_sys::{initialize_webf_api, ExecutingContext, RustValue};

pub mod async_storage;
pub mod navigator;
pub mod storage;

#[no_mangle]
pub extern "C" fn init_webf_test_app(handle: RustValue<ExecutingContextRustMethods>) -> *mut c_void {
  let context: ExecutingContext = initialize_webf_api(handle);

  webf_test_utils::sync_runner::run_tests(context.clone());

  webf_sys::webf_future::spawn(context.clone(), async move {
    webf_test_utils::async_runner::run_tests(context.clone()).await;
  });

  std::ptr::null_mut()
}
