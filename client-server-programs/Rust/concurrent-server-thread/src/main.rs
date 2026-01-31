mod utils;
use utils::handle_client::handle_client;

use std::net::TcpListener;
use std::thread;

fn main() {

    let concurrent_server_socket = TcpListener::bind("192.168.2.57:2222").unwrap();
    println!("Concurrent server successfully started and running....");

    for incoming_request in concurrent_server_socket.incoming(){
       let mut client_stream = incoming_request.unwrap();
       thread::spawn( move || {
        handle_client(client_stream)
       });
    }
   
}
