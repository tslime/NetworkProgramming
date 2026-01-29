use std::net::{TcpListener,TcpStream};
use std::io::{Read,Write};


mod utils;
use utils::handle_client::handle_client;


fn main(){

    let server_socket = TcpListener::bind("192.168.2.57:2222").unwrap();
    println!("Server running.... \n");
    let (mut stream,address) = server_socket.accept().unwrap();
    
    
    loop{
        handle_client(&mut stream);
        stream.write_all(b"message received! \n\n").unwrap();
    };
  
}