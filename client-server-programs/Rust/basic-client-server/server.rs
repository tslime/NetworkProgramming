use std::net::TcpListener;
use std::io::Read;

fn main(){

    let server_socket = TcpListener::bind("192.168.2.57:2222").unwrap();
    println!("Server running.... \n");
    
    let (mut stream,address) = server_socket.accept().unwrap();
    let mut buffer = [0;512];
    let bytes_read = stream.read(&mut buffer).unwrap();

    let message = String::from_utf8_lossy(&buffer[..bytes_read]);

    println!("client message: {}",message);
}