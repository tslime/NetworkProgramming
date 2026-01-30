mod utils;
use utils::handle_client::handle_client;

use std::net::TcpListener;
use std::thread;

fn main() {

    let concurrent_server_socket = TcpListener::bind("192.168.2.57:2222").unwrap();
    println!("Concurrent successfully started and running....");

    
}
