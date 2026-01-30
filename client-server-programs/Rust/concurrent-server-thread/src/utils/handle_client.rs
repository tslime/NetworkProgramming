use std::net::{TcpListener,TcpStream};
use std::io::{Read,Write};

pub fn handle_client(client_stream: &mut TcpStream){
    let mut buffer = [0;512];

    let bytes_read = client_stream.read(&mut buffer).unwrap();
    let message = String::from_utf8_lossy(&buffer[..bytes_read]);
    println!("client message: {}",message);
}