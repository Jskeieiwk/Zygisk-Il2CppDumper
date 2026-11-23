//! IL2CPP runtime adapter.
//!
//! Target `libil2cpp.so` for Build ID 76e47a1a… strips standard `il2cpp_*`
//! exports; the C++ project's `native/runtime_12034.h` keeps the RVA table used
//! as a fallback. This file declares the typed function pointers Rust code
//! calls through, plus the resolver skeleton.
//!
//! PORT STATUS: the API types are complete. The resolver body is a TODO.
//! Mirror `oxide_features.cpp:170-295` (`resolve()`) line-by-line.
use std::ffi::{c_char, c_void};
use std::ptr;

pub type Object = c_void;
pub type Method = c_void;
pub type Class = c_void;
pub type Image = c_void;
pub type Domain = c_void;
pub type Assembly = c_void;
pub type Type = c_void;

#[repr(C)]
#[derive(Clone, Copy, Debug, Default)]
pub struct Vec3 { pub x: f32, pub y: f32, pub z: f32 }

#[repr(C)]
#[derive(Clone, Copy, Debug, Default)]
pub struct Vec2 { pub x: f32, pub y: f32 }

#[repr(C)]
#[derive(Clone, Copy, Debug, Default)]
pub struct Color { pub r: f32, pub g: f32, pub b: f32, pub a: f32 }

#[repr(C)]
#[derive(Clone, Copy)]
pub struct Matrix { pub v: [f32; 16] }

/// IL2CPP managed array header (same layout for all T[]).
#[repr(C)]
pub struct Array {
    pub klass: *mut c_void,
    pub monitor: *mut c_void,
    pub bounds: *mut c_void,
    pub length: usize,
    /// First slot — the rest trail. Use `items_slice` to read as `[*mut Object]`.
    pub first: *mut Object,
}

impl Array {
    /// SAFETY: Caller must ensure `length` matches the actual slot count.
    pub unsafe fn items_slice(&self) -> &[*mut Object] {
        let base = &self.first as *const *mut Object;
        std::slice::from_raw_parts(base, self.length)
    }
}

#[derive(Default)]
pub struct Api {
    pub domain_get: Option<unsafe extern "C" fn() -> *mut Domain>,
    pub thread_attach: Option<unsafe extern "C" fn(*mut Domain) -> *mut c_void>,
    pub thread_detach: Option<unsafe extern "C" fn(*mut c_void)>,
    pub domain_get_assemblies:
        Option<unsafe extern "C" fn(*mut Domain, *mut usize) -> *const *const Assembly>,
    pub assembly_get_image: Option<unsafe extern "C" fn(*const Assembly) -> *mut Image>,
    pub image_get_name: Option<unsafe extern "C" fn(*mut Image) -> *const c_char>,
    pub class_from_name:
        Option<unsafe extern "C" fn(*mut Image, *const c_char, *const c_char) -> *mut Class>,
    pub class_get_method_from_name:
        Option<unsafe extern "C" fn(*mut Class, *const c_char, i32) -> *mut Method>,
    pub class_get_methods:
        Option<unsafe extern "C" fn(*mut Class, *mut *mut c_void) -> *mut Method>,
    pub method_get_name: Option<unsafe extern "C" fn(*mut Method) -> *const c_char>,
    pub method_get_param_count: Option<unsafe extern "C" fn(*mut Method) -> u32>,
    pub method_get_param: Option<unsafe extern "C" fn(*mut Method, u32) -> *const Type>,
    pub type_get_type: Option<unsafe extern "C" fn(*const Type) -> i32>,
    pub class_get_type: Option<unsafe extern "C" fn(*mut Class) -> *const Type>,
    pub type_get_object: Option<unsafe extern "C" fn(*const Type) -> *mut Object>,
    pub runtime_invoke: Option<
        unsafe extern "C" fn(
            *mut Method,
            *mut c_void,
            *mut *mut c_void,
            *mut *mut Object,
        ) -> *mut Object,
    >,
    pub object_unbox: Option<unsafe extern "C" fn(*mut Object) -> *mut c_void>,
    pub string_chars: Option<unsafe extern "C" fn(*mut Object) -> *const u16>,
    pub string_length: Option<unsafe extern "C" fn(*mut Object) -> i32>,
    pub string_new: Option<unsafe extern "C" fn(*const c_char) -> *mut Object>,
    pub gchandle_new: Option<unsafe extern "C" fn(*mut Object, bool) -> usize>,
    pub gchandle_get_target: Option<unsafe extern "C" fn(usize) -> *mut Object>,
    pub gchandle_free: Option<unsafe extern "C" fn(usize)>,
    pub object_get_class: Option<unsafe extern "C" fn(*mut Object) -> *mut Class>,
    pub class_is_assignable_from: Option<unsafe extern "C" fn(*mut Class, *mut Class) -> bool>,
}

/// Resolve the whole API table. Returns `None` if any required symbol is
/// missing — the caller must treat this as a hard fail.
pub unsafe fn resolve_api(_base: usize) -> Option<Api> {
    // TODO PORT: oxide_features.cpp:170-185 BIND macro. For each name:
    //   1. dlopen(game_path(), RTLD_NOW | RTLD_NOLOAD) -> handle
    //   2. dlsym(handle, "il2cpp_<name>") — most strip to null on this build
    //   3. fall back to runtime_12034::entry(base, "<name>")
    //   4. if still null, return None
    //
    // Keep every pointer as `Option<unsafe extern "C" fn ...>`, use
    // mem::transmute from `*mut c_void`. There are 25 entries in the C++ BIND
    // list; do not reorder — downstream relies on the typed signatures.
    None
}

pub unsafe fn call(
    api: &Api,
    method: *mut Method,
    this: *mut c_void,
    args: &mut [*mut c_void],
) -> *mut Object {
    if method.is_null() { return ptr::null_mut(); }
    let Some(invoke) = api.runtime_invoke else { return ptr::null_mut(); };
    let mut exc: *mut Object = ptr::null_mut();
    let ret = invoke(method, this, args.as_mut_ptr(), &mut exc);
    if exc.is_null() { ret } else { ptr::null_mut() }
}

pub unsafe fn unbox_copy<T: Copy>(api: &Api, object: *mut Object) -> Option<T> {
    if object.is_null() { return None; }
    let unbox = api.object_unbox?;
    let p = unbox(object);
    if p.is_null() { return None; }
    Some(std::ptr::read_unaligned(p as *const T))
}
