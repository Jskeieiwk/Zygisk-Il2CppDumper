// Links Dobby built by the existing C++ pipeline. build.sh runs the Dobby
// CMake first and sets DOBBY_LIB_DIR before invoking cargo.
fn main() {
    let dir = std::env::var("DOBBY_LIB_DIR")
        .expect("DOBBY_LIB_DIR must point to the directory containing libdobby.a");
    println!("cargo:rustc-link-search=native={dir}");
    println!("cargo:rustc-link-lib=static=dobby");
    println!("cargo:rustc-link-lib=dylib=log");
    println!("cargo:rustc-link-lib=dylib=dl");
    // The Dobby static archive is C++ and uses libc++ bits even with -static-libstdc++.
    println!("cargo:rustc-link-lib=dylib=c++_shared");
    println!("cargo:rerun-if-env-changed=DOBBY_LIB_DIR");
}
