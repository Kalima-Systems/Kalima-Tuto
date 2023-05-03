#![allow(non_snake_case)]
#![allow(dead_code)]

use std::ffi::CString;

pub fn input_to_i8(input: &str) -> Vec<i8> {
    let vec: Vec<u8> = (CString::new(String::from(input)).unwrap()).into_bytes_with_nul();
    let tmp: Vec<i8> = vec.into_iter().map(|c| c as i8).collect::<_>();
    return tmp;
}

pub fn print_u8(input: *mut u8, size: usize){
    unsafe{
        println!("{:?}", String::from_utf8_lossy(core::slice::from_raw_parts_mut(input, size)));
    }
}

pub fn print_i8(input: *mut i8, size: usize){
    unsafe{
        println!("{:?}", String::from_utf8_lossy(core::slice::from_raw_parts_mut(input as *mut u8, size)));
    }
}