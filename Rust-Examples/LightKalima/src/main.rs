#![allow(non_snake_case)]

use std::{thread, time::Duration};
use std::ptr;
mod util;

fn main() {
    unsafe{
        let mut retry: bool = true;
        let mut vec_file = util::input_to_i8("etc/cfg/config.txt");
        let bytes_file: *mut i8 = vec_file.as_mut_ptr();
        let node = kalima::bindings::create_Node(bytes_file, ptr::null_mut());
        println!("Config loaded");
        kalima::bindings::Connect_to_Notaries(node);
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
    let msg_size = input.len() as i32;
    let mut vec_msg = util::input_to_i8(&*input);
    let msg: *mut i8 = vec_msg.as_mut_ptr();
    unsafe{
        let kprops = kalima::bindings::new_propList();
        let mut vec_ttl = util::input_to_i8("ttl");
        let ttl: *mut i8 = vec_ttl.as_mut_ptr();
        let mut vec_time = util::input_to_i8("-1");
        let time: *mut i8 = vec_time.as_mut_ptr();
        kalima::bindings::set_prop(kprops, ttl, 3, time, 2);

        let mut vec_type = util::input_to_i8("PUB");
        let ttype: *mut i8 = vec_type.as_mut_ptr();
        let mut vec_addr = util::input_to_i8("...");             //TO CHANGE (ex : "/sensors")
        let addr: *mut i8 = vec_addr.as_mut_ptr();
        let mut vec_key = util::input_to_i8("Default message");
        let key: *mut i8 = vec_key.as_mut_ptr();
        let kmsg = kalima::bindings::getMessage((*node).devid, kalima::bindings::UUID_SIZE as i32, kalima::bindings::get_encoded_Type(ttype) as i8, addr, kalima::bindings::strlen(addr) as i32, key, kalima::bindings::strlen(key) as i32, 1, msg, msg_size, kprops);
        kalima::bindings::send_KMessage(node, (*kmsg).Kmessage);
    }
    println!("Message sent");
}

fn send_modulable_message(node: *mut kalima::bindings::Node){
    unsafe{
        let kprops = kalima::bindings::new_propList();
        let mut vec_ttl = util::input_to_i8("ttl");
        let ttl: *mut i8 = vec_ttl.as_mut_ptr();
        let mut vec_time = util::input_to_i8("-1");
        let time: *mut i8 = vec_time.as_mut_ptr();
        kalima::bindings::set_prop(kprops, ttl, 3, time, 2);

        let mut vec_type = util::input_to_i8("PUB");
        let ttype: *mut i8 = vec_type.as_mut_ptr();

        println!("Type the address you want to interact with :");
        let input1 = get_input();
        let addr_size = input1.len() as i32;
        let mut vec_addr = util::input_to_i8(&*input1);
        let addr: *mut i8 = vec_addr.as_mut_ptr();

        println!("Type the key of you choice :");
        let input2 = get_input();
        let key_size = input2.len() as i32;
        let mut vec_key = util::input_to_i8(&*input2);
        let key: *mut i8 = vec_key.as_mut_ptr();

        println!("Type the message of you choice :");
        let input3 = get_input();
        let msg_size = input3.len() as i32;
        let mut vec_msg = util::input_to_i8(&*input3);
        let msg: *mut i8 = vec_msg.as_mut_ptr();

        let kmsg = kalima::bindings::getMessage((*node).devid, kalima::bindings::UUID_SIZE as i32, kalima::bindings::get_encoded_Type(ttype) as i8, addr, addr_size, key, key_size, 1, msg, msg_size, kprops);
        kalima::bindings::send_KMessage(node, (*kmsg).Kmessage);
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