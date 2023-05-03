#![allow(non_snake_case)]

use std::{thread, time::Duration};
mod util;
mod callback;

fn main() {
    unsafe{
        let mut retry: bool = true;
        let mut vec_list_path = util::input_to_i8("Files/LuaScripts/");
        let list_path: *mut i8 = vec_list_path.as_mut_ptr();
        let contract_list = kalima::bindings::new_ContractList(list_path, 1);
        let list_ptr: *mut ::std::os::raw::c_void = contract_list as *mut ::std::os::raw::c_void;

        let mut vec_file = util::input_to_i8("etc/cfg/config.txt");
        let bytes_file: *mut i8 = vec_file.as_mut_ptr();
        let node = kalima::bindings::create_Node(bytes_file, list_ptr);

        kalima::bindings::set_contractList_log_path((*(*node).config).log_Path, (*(*node).config).LogPath_size as i32);
        println!("Config loaded");
        kalima::bindings::Connect_to_Notaries(node);
        let clientCallback = callback::set_clientCallback();
        kalima::bindings::add_ClientCallback(node, clientCallback);
        thread::sleep(Duration::from_millis(2000));
        println!("GO!");
        menu();
        while retry == true {
            let user_input = get_input();
            match user_input.as_str() {
                "1" => {
                    println!("default");
                    send_default_message(node);
                    retry = true;
                }
                "2" => {
                    println!("modulable");
                    send_modulable_message(node);
                    retry = true;
                }
                "3" => {
                    println!("Close");
                    retry = false;
                }
                _ => {
                    println!("Incorrect, retry");
                }
            }
        }
    }
    
}

fn send_default_message(node: *mut kalima::bindings::Node){
    println!("Message to send to Blockchain :");
    let input = get_input();
    let msg_size = input.len() as u16;
    let mut vec_msg = util::input_to_i8(&*input);
    let msg: *mut i8 = vec_msg.as_mut_ptr();
    unsafe{
        let mut vec_addr = util::input_to_i8("...");                     //TO CHANGE (ex : "/sensors")
        let addr: *mut i8 = vec_addr.as_mut_ptr();
        let mut vec_key = util::input_to_i8("Default message");
        let key: *mut i8 = vec_key.as_mut_ptr();
        kalima::bindings::put_msg_default((*node).clone, addr, kalima::bindings::strlen(addr) as u8, key, kalima::bindings::strlen(key) as u8, msg, msg_size);
    }
    println!("Message sent");
}

fn send_modulable_message(node: *mut kalima::bindings::Node){
    unsafe{
        println!("Type the address you want to interact with :");
        let input1 = get_input();
        let addr_size = input1.len() as u8;
        let mut vec_addr = util::input_to_i8(&*input1);
        let addr: *mut i8 = vec_addr.as_mut_ptr();

        println!("Type the key of you choice :");
        let input2 = get_input();
        let key_size = input2.len() as u8;
        let mut vec_key = util::input_to_i8(&*input2);
        let key: *mut i8 = vec_key.as_mut_ptr();

        println!("Type the message of you choice :");
        let input3 = get_input();
        let msg_size = input3.len() as u16;
        let mut vec_msg = util::input_to_i8(&*input3);
        let msg: *mut i8 = vec_msg.as_mut_ptr();

        kalima::bindings::put_msg_default((*node).clone, addr, addr_size, key, key_size, msg, msg_size);
    }
    println!("Message sent");
}

fn menu(){
    println!("commands available :");
    println!("- 1 ==> Send a message with default settings");
    println!("- 2 ==> Send a modulable message");
    println!("- 3 ==> Close");
}

fn get_input() -> String {
    let mut user_input = String::new();
    std::io::stdin().read_line(&mut user_input).unwrap();
    if let Some('\n')=user_input.chars().next_back() {
        user_input.pop();
    }
    if let Some('\r')=user_input.chars().next_back() {
        user_input.pop();
    }
    return user_input;
}