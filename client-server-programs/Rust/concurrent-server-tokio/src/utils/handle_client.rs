use std::net::{TcpListener,TcpStream};
use std::io::{Read,Write};

pub fn handle_client(mut client_stream: TcpStream){
    let mut buffer = [0;512];

    loop{
        let bytes_read = client_stream.read(&mut buffer).unwrap();
        let message = String::from_utf8_lossy(&buffer[..bytes_read]);
        println!("client message: {}",message);
        client_stream.write_all(b"Message received\n").unwrap();
    };
}