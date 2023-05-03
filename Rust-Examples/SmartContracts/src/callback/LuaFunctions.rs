#![allow(non_snake_case)]

use std::ptr;
use crate::util;

extern fn LuaGetBody(L: *mut kalima::bindings::lua_State) -> i32 {
    unsafe{
        let kmsg_ptr = kalima::bindings::lua_touserdata(L,1);
        let kmsg = kmsg_ptr as *mut kalima::bindings::KMsg;
        let body = kalima::bindings::getBody(kmsg) as *mut i8;
        kalima::bindings::lua_pushstring(L,body);
        return 1;
    }
}
pub const LUA_GET_BODY: ::std::option::Option<unsafe extern "C" fn(*mut kalima::bindings::lua_State) -> i32> = Some(LuaGetBody);

extern fn LuaGetKey(L: *mut kalima::bindings::lua_State) -> i32 {
    unsafe{
        let kmsg_ptr = kalima::bindings::lua_touserdata(L,1);
        let kmsg = kmsg_ptr as *mut kalima::bindings::KMsg;
        let key = kalima::bindings::getKey(kmsg) as *mut i8;
        kalima::bindings::lua_pushstring(L,key);
        return 1;
    }
}
pub const LUA_GET_KEY: ::std::option::Option<unsafe extern "C" fn(*mut kalima::bindings::lua_State) -> i32> = Some(LuaGetKey);

extern fn LuaPutLog(L: *mut kalima::bindings::lua_State) -> i32 {
    unsafe{
        let node_ptr = kalima::bindings::lua_touserdata(L,1);
        let node = node_ptr as *mut kalima::bindings::Node;
        let log = kalima::bindings::lua_tolstring(L, 2, ptr::null_mut()) as *mut i8;
        let mut vec_main = util::input_to_i8("Main");
        let main: *mut i8 = vec_main.as_mut_ptr();
        let mut vec_log = util::input_to_i8("Log");
        let logname: *mut i8 = vec_log.as_mut_ptr();                      
        kalima::bindings::log_srvMsg((*(*node).config).log_Path, main, logname, kalima::bindings::INFO as u8, log);
    }
    return 0;
}
pub const LUA_PUT_LOG: ::std::option::Option<unsafe extern "C" fn(*mut kalima::bindings::lua_State) -> i32> = Some(LuaPutLog);

extern fn LuaPutMsg(L: *mut kalima::bindings::lua_State) -> i32 {
    unsafe{
        let node_ptr = kalima::bindings::lua_touserdata(L,1);
        let node = node_ptr as *mut kalima::bindings::Node;
        let address = kalima::bindings::lua_tolstring(L, 2, ptr::null_mut()) as *mut i8;
        let address_size = kalima::bindings::lua_tonumber(L,3) as i8;
        let key = kalima::bindings::lua_tolstring(L, 4, ptr::null_mut()) as *mut i8;
        let key_size = kalima::bindings::lua_tonumber(L,5) as i8;
        let body = kalima::bindings::lua_tolstring(L, 6, ptr::null_mut()) as *mut i8;
        let body_size = kalima::bindings::lua_tonumber(L,7) as i8;
        kalima::bindings::put_msg_default((*node).clone, address, address_size as u8, key, key_size as u8, body, body_size as u16);
    }
    return 0;
}
pub const LUA_PUT_MSG: ::std::option::Option<unsafe extern "C" fn(*mut kalima::bindings::lua_State) -> i32> = Some(LuaPutMsg);

extern fn LuaStrLen(L: *mut kalima::bindings::lua_State) -> i32 {
    unsafe{
        let string = kalima::bindings::lua_tolstring(L, 1, ptr::null_mut()) as *mut i8;
        let size = kalima::bindings::strlen(string) as isize;
        kalima::bindings::lua_pushinteger(L, size);
    }
    return 1;
}
pub const LUA_STR_LEN: ::std::option::Option<unsafe extern "C" fn(*mut kalima::bindings::lua_State) -> i32> = Some(LuaStrLen);