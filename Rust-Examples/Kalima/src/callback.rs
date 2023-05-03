#![allow(non_snake_case)]

use crate::util;

extern fn c_send(_Kmessage: *mut kalima::bindings::KMessage){

}
const ON_SEND: kalima::bindings::ClientCallback_send = Some(c_send);

extern fn onNewAddress(_node_ptr: *mut ::std::os::raw::c_void, _address: *mut ::std::os::raw::c_char, _address_size: u8){
    
}
const ON_NEW: kalima::bindings::ClientCallback_onNewAddress = Some(onNewAddress);

extern fn onAddressSynchronized(_node_ptr: *mut ::std::os::raw::c_void, _address: *mut ::std::os::raw::c_char, _address_size: u8){
    let node = _node_ptr as *mut kalima::bindings::Node;
    unsafe{
        let addr = String::from_utf8_lossy(core::slice::from_raw_parts_mut(_address as *mut u8, _address_size as usize));
        if &addr == "..." {                                                                //TO CHANGE (ex : "/sensors")
            let memcacheCallback= set_memcacheCallback();
            kalima::bindings::add_MemCacheCallback((*node).clone, memcacheCallback);
        }
    }
}
const ON_SYNC: kalima::bindings::ClientCallback_onAddressSynchronized = Some(onAddressSynchronized);

extern fn onReject(_client_ptr: *mut ::std::os::raw::c_void){
    
}
const ON_REJ: kalima::bindings::ClientCallback_onReject = Some(onReject);

extern fn putData(_clone_ptr: *mut ::std::os::raw::c_void, _Kmessage: *mut kalima::bindings::KMessage){
    unsafe{
        let _clone = _clone_ptr as *mut kalima::bindings::Clone;
        let kmsg = kalima::bindings::setMessage(_Kmessage);
        let address = String::from_utf8_lossy(core::slice::from_raw_parts_mut(kalima::bindings::getAddress(kmsg) as *mut u8, kalima::bindings::getAddressSize(kmsg) as usize));
        let key = String::from_utf8_lossy(core::slice::from_raw_parts_mut(kalima::bindings::getKey(kmsg) as *mut u8, kalima::bindings::getKeySize(kmsg) as usize));
        let body = String::from_utf8_lossy(core::slice::from_raw_parts_mut(kalima::bindings::getBody(kmsg) as *mut u8, kalima::bindings::getBodySize(kmsg) as usize));
        println!("Message added on address : {:?} / Key : {:?} / Body : {:?}", address, key, body);
    }
}
const PUT_DATA: kalima::bindings::MemCacheCallback_putData = Some(putData);

extern fn removeData(_clone_ptr: *mut ::std::os::raw::c_void, _Kmessage: *mut kalima::bindings::KMessage){

}
const REMOVE_DATA: kalima::bindings::MemCacheCallback_removeData = Some(removeData);

pub fn set_clientCallback() -> *mut kalima::bindings::ClientCallback {
    return unsafe {kalima::bindings::new_ClientCallback(ON_SEND, ON_NEW, ON_SYNC, ON_REJ)};
}

pub fn set_memcacheCallback() -> *mut kalima::bindings::MemCacheCallback {
    let mut vec_addr= util::input_to_i8("...");                                              //TO CHANGE (ex : "/sensors")
    let addr: *mut i8 = vec_addr.as_mut_ptr();

    return unsafe {kalima::bindings::new_MemCacheCallback(PUT_DATA, REMOVE_DATA, addr)};
}