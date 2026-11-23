//! Thin logcat wrapper. Avoids dragging in the `log` + `android_logger` stack.
use std::ffi::{c_char, c_int, CString};

#[repr(i32)]
#[allow(dead_code)]
pub enum Priority {
    Info = 4,
    Warn = 5,
    Error = 6,
}

extern "C" {
    fn __android_log_write(prio: c_int, tag: *const c_char, msg: *const c_char) -> c_int;
}

/// Write one short log line under the branded tag. Long messages are the exact
/// surface we spent the C++ pass stripping — keep callers terse.
pub fn write(prio: Priority, msg: &str) {
    // Truncate to 256 bytes so a logic bug can't flood logcat.
    let trimmed: &str = if msg.len() > 255 { &msg[..255] } else { msg };
    let tag = match CString::new(shared::BRAND_TAG) { Ok(c) => c, Err(_) => return };
    let message = match CString::new(trimmed) { Ok(c) => c, Err(_) => return };
    unsafe { __android_log_write(prio as c_int, tag.as_ptr(), message.as_ptr()); }
}

#[macro_export]
macro_rules! log_info {
    ($($arg:tt)*) => {
        $crate::log::write($crate::log::Priority::Info, &format!($($arg)*))
    };
}

#[macro_export]
macro_rules! log_err {
    ($($arg:tt)*) => {
        $crate::log::write($crate::log::Priority::Error, &format!($($arg)*))
    };
}
