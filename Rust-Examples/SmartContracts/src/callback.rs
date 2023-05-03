#![allow(non_snake_case)]

use std::ptr;
use std::slice;
use crate::util;
mod LuaFunctions;

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
        if &addr == "..." {                                                                                                      //TO CHANGE (ex : "/sensors")
            let memcacheCallback= set_memcacheCallback();
            kalima::bindings::add_MemCacheCallback((*node).clone, memcacheCallback);
        }
        if addr.starts_with("/Kalima_Contracts") == true {
            let list = (*node).contract_list as *mut kalima::bindings::ContractList;
            let memcache = kalima::bindings::getMemCache((*node).clone, _address, _address_size);
            let mut kvmap = kalima::bindings::SkipListGetFirst((*memcache).kvmap);
            while kvmap != ptr::null_mut() {
                let sl_kv = (*kvmap).key as *mut kalima::bindings::KeyValueObj;
                let buffer :&[u8] = slice::from_raw_parts((*sl_kv).value as *const u8, (*sl_kv).value_size as usize);
                let b = &buffer[4..];
                let mut vec = Vec::from(b);
                let sl_kv_value: *mut u8 = vec.as_mut_ptr();

                let msg = kalima::bindings::build(sl_kv_value);
                let kmsg = kalima::bindings::setMessage(msg);
                let key = String::from_utf8_lossy(core::slice::from_raw_parts_mut(kalima::bindings::getKey(kmsg) as *mut u8, kalima::bindings::getKeySize(kmsg) as usize));
                if key.ends_with(".lua") == true {
                    let mut vec_key = util::input_to_i8(&*key.to_string());
                    let key_mut: *mut i8 = vec_key.as_mut_ptr();

                    let mut vec_propname = util::input_to_i8("downloadURL");
                    let propname: *mut i8 = vec_propname.as_mut_ptr();
                    let url = kalima::bindings::getProp(kmsg, propname) as *mut i8;

                    kalima::bindings::curl_req(url, key_mut, (*list).Contract_path);

                    for i in 0..kalima::bindings::nb_of_elements((*list).List) {
                        let lua_list = kalima::bindings::list_get_element((*list).List, i);
                        let lua_script = (*lua_list).data as *mut kalima::bindings::Lua;
                        let script_name = String::from_utf8_lossy(core::slice::from_raw_parts_mut((*lua_script).filename as *mut u8, kalima::bindings::getKeySize(kmsg) as usize));
                        if script_name == key {
                            let mut vec_sig = util::input_to_i8("signature");
                            let sig: *mut i8 = vec_sig.as_mut_ptr();
                            let signature = kalima::bindings::getProp(kmsg, sig) as *mut i8;
                            let mut vec_aesk = util::input_to_i8("aesKey");
                            let aesk: *mut i8 = vec_aesk.as_mut_ptr();
                            let aes_key = kalima::bindings::getProp(kmsg, aesk) as *mut i8;
                            let mut vec_aesi = util::input_to_i8("aesIV");
                            let aesi: *mut i8 = vec_aesi.as_mut_ptr();
                            let aes_iv = kalima::bindings::getProp(kmsg, aesi) as *mut i8;

                            kalima::bindings::decrypt_Lua_script(lua_script, (*lua_script).filepath, signature, aes_key, aes_iv);
                        }
                    }
                }

                kvmap = (*kvmap).forward[0];
            }
        }
    }
}
const ON_SYNC: kalima::bindings::ClientCallback_onAddressSynchronized = Some(onAddressSynchronized);

extern fn onReject(_client_ptr: *mut ::std::os::raw::c_void){
    
}
const ON_REJ: kalima::bindings::ClientCallback_onReject = Some(onReject);

extern fn putData(_clone_ptr: *mut ::std::os::raw::c_void, _Kmessage: *mut kalima::bindings::KMessage){
    unsafe{
        let clone = _clone_ptr as *mut kalima::bindings::Clone;
        let contract_list = (*(*clone).node).contract_list as *mut kalima::bindings::ContractList;
        let kmsg = kalima::bindings::setMessage(_Kmessage);
        let address = String::from_utf8_lossy(core::slice::from_raw_parts_mut(kalima::bindings::getAddress(kmsg) as *mut u8, kalima::bindings::getAddressSize(kmsg) as usize));
        let key = String::from_utf8_lossy(core::slice::from_raw_parts_mut(kalima::bindings::getKey(kmsg) as *mut u8, kalima::bindings::getKeySize(kmsg) as usize));
        let body = String::from_utf8_lossy(core::slice::from_raw_parts_mut(kalima::bindings::getBody(kmsg) as *mut u8, kalima::bindings::getBodySize(kmsg) as usize));
        println!("Message added on address : {:?} / Key : {:?} / Body : {:?}", address, key, body);

        if contract_list != ptr::null_mut() {
            let mut vec_name = util::input_to_i8("sensors.lua");
            let name: *mut i8 = vec_name.as_mut_ptr(); 
            let Lua_contract = kalima::bindings::load_Contract(contract_list, name);
            if Lua_contract == ptr::null_mut() {return;}

            let mut vec_main = util::input_to_i8("main");
            let main: *mut i8 = vec_main.as_mut_ptr();
            kalima::bindings::lua_getfield((*Lua_contract).L, kalima::bindings::LUA_GLOBALSINDEX, main);

            let mut vec_bodyfunc= util::input_to_i8("LuaGetBody");
            let bodyfunc: *mut i8 = vec_bodyfunc.as_mut_ptr();
            kalima::bindings::lua_pushcclosure((*Lua_contract).L, LuaFunctions::LUA_GET_BODY, 0);
            kalima::bindings::lua_setfield((*Lua_contract).L, kalima::bindings::LUA_GLOBALSINDEX, bodyfunc);

            let mut vec_keyfunc= util::input_to_i8("LuaGetKey");
            let keyfunc: *mut i8 = vec_keyfunc.as_mut_ptr();
            kalima::bindings::lua_pushcclosure((*Lua_contract).L, LuaFunctions::LUA_GET_KEY, 0);
            kalima::bindings::lua_setfield((*Lua_contract).L, kalima::bindings::LUA_GLOBALSINDEX, keyfunc);

            let mut vec_putfunc= util::input_to_i8("LuaPutMsg");
            let putfunc: *mut i8 = vec_putfunc.as_mut_ptr();
            kalima::bindings::lua_pushcclosure((*Lua_contract).L, LuaFunctions::LUA_PUT_MSG, 0);
            kalima::bindings::lua_setfield((*Lua_contract).L, kalima::bindings::LUA_GLOBALSINDEX, putfunc);

            let mut vec_logfunc= util::input_to_i8("LuaPutLog");
            let logfunc: *mut i8 = vec_logfunc.as_mut_ptr();
            kalima::bindings::lua_pushcclosure((*Lua_contract).L, LuaFunctions::LUA_PUT_LOG, 0);
            kalima::bindings::lua_setfield((*Lua_contract).L, kalima::bindings::LUA_GLOBALSINDEX, logfunc);

            let mut vec_lenfunc= util::input_to_i8("LuaStrLen");
            let lenfunc: *mut i8 = vec_lenfunc.as_mut_ptr();
            kalima::bindings::lua_pushcclosure((*Lua_contract).L, LuaFunctions::LUA_STR_LEN, 0);
            kalima::bindings::lua_setfield((*Lua_contract).L, kalima::bindings::LUA_GLOBALSINDEX, lenfunc);

            kalima::bindings::lua_pushlightuserdata((*Lua_contract).L,kmsg as *mut ::std::os::raw::c_void);
            kalima::bindings::lua_pushlightuserdata((*Lua_contract).L,(*clone).node as *mut ::std::os::raw::c_void);
            kalima::bindings::lua_pcall((*Lua_contract).L, 2, 0, 0);
        }
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
    let mut vec_addr= util::input_to_i8("...");                                                     //TO CHANGE (ex : "/sensors")
    let addr: *mut i8 = vec_addr.as_mut_ptr();

    return unsafe {kalima::bindings::new_MemCacheCallback(PUT_DATA, REMOVE_DATA, addr)};
}