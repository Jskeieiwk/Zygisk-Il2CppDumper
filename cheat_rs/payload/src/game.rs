//! Locates `libil2cpp.so` in the host process and verifies the Build ID.
use std::ffi::{c_char, c_int, c_void, CStr};
use std::mem;
use std::sync::atomic::{AtomicBool, AtomicUsize, Ordering};
use std::sync::OnceLock;

use shared::{PLAYER_LATE_UPDATE, PLAYER_UPDATE, TARGET_BUILD_ID};

pub static BASE: AtomicUsize = AtomicUsize::new(0);
pub static BUILD_ID_OK: AtomicBool = AtomicBool::new(false);
static GAME_PATH: OnceLock<String> = OnceLock::new();

#[repr(C)]
struct DlPhdrInfo {
    dlpi_addr: usize,
    dlpi_name: *const c_char,
    dlpi_phdr: *const Elf64Phdr,
    dlpi_phnum: u16,
    // trailing fields intentionally omitted; our callback uses only the above.
}

#[repr(C)]
struct Elf64Phdr {
    p_type: u32,
    p_flags: u32,
    p_offset: u64,
    p_vaddr: u64,
    p_paddr: u64,
    p_filesz: u64,
    p_memsz: u64,
    p_align: u64,
}

#[repr(C)]
struct Elf64Nhdr {
    n_namesz: u32,
    n_descsz: u32,
    n_type: u32,
}

const PT_NOTE: u32 = 4;
const NT_GNU_BUILD_ID: u32 = 3;

extern "C" {
    fn dl_iterate_phdr(
        cb: extern "C" fn(*mut DlPhdrInfo, usize, *mut c_void) -> c_int,
        data: *mut c_void,
    ) -> c_int;
}

pub fn locate() -> bool {
    extern "C" fn cb(info: *mut DlPhdrInfo, _size: usize, _data: *mut c_void) -> c_int {
        unsafe {
            let info = &*info;
            if info.dlpi_name.is_null() { return 0; }
            let name = match CStr::from_ptr(info.dlpi_name).to_str() {
                Ok(s) => s,
                Err(_) => return 0,
            };
            if !name.ends_with("/libil2cpp.so") { return 0; }

            BASE.store(info.dlpi_addr, Ordering::Release);
            let _ = GAME_PATH.set(name.to_owned());

            for i in 0..info.dlpi_phnum as isize {
                let ph = &*info.dlpi_phdr.offset(i);
                if ph.p_type != PT_NOTE || ph.p_memsz > 4096 { continue; }
                let data = (info.dlpi_addr + ph.p_vaddr as usize) as *const u8;
                let mut at: usize = 0;
                while at + mem::size_of::<Elf64Nhdr>() <= ph.p_memsz as usize {
                    let note = &*(data.add(at) as *const Elf64Nhdr);
                    let names = ((note.n_namesz as usize + 3) & !3) as usize;
                    let desc_sz = ((note.n_descsz as usize + 3) & !3) as usize;
                    let step = mem::size_of::<Elf64Nhdr>() + names + desc_sz;
                    if step == 0 || at + step > ph.p_memsz as usize { break; }
                    let name_ptr = data.add(at + mem::size_of::<Elf64Nhdr>());
                    let desc_ptr = name_ptr.add(names);
                    let is_gnu = note.n_namesz >= 4
                        && std::slice::from_raw_parts(name_ptr, 4) == b"GNU\0";
                    if note.n_type == NT_GNU_BUILD_ID
                        && is_gnu
                        && note.n_descsz as usize == TARGET_BUILD_ID.len()
                    {
                        let actual = std::slice::from_raw_parts(desc_ptr, TARGET_BUILD_ID.len());
                        if actual == TARGET_BUILD_ID {
                            BUILD_ID_OK.store(true, Ordering::Release);
                        }
                    }
                    at += step;
                }
            }
            1
        }
    }
    unsafe { dl_iterate_phdr(cb, std::ptr::null_mut()) != 0 }
}

pub fn signature_matches() -> bool {
    let base = BASE.load(Ordering::Acquire);
    if base == 0 || !BUILD_ID_OK.load(Ordering::Acquire) { return false; }
    unsafe {
        let a = std::ptr::read_volatile((base + PLAYER_LATE_UPDATE.0) as *const u32);
        let b = std::ptr::read_volatile((base + PLAYER_UPDATE.0) as *const u32);
        a == PLAYER_LATE_UPDATE.1 && b == PLAYER_UPDATE.1
    }
}

#[allow(dead_code)]
pub fn game_path() -> Option<&'static str> { GAME_PATH.get().map(|s| s.as_str()) }
