use std::net::{TcpListener,TcpStream};
use std::io::{Read,Write};
use std::error;
use log::{error,info,warn,debug,trace};

pub fn handle_client(mut client_stream: TcpStream) -> Result<(),Box<dyn error::Error>> {
    let mut buffer = [0;512];

    loop{
        let bytes_read = client_stream.read(&mut buffer).map_err(|e| {error!("Failed to read data {}", e);e})?;
         if bytes_read == 0 {
            break;
        }

        let message = String::from_utf8_lossy(&buffer[..bytes_read]);
        println!("client message: {}",message);
        client_stream.write_all(b"Message received\n").map_err(|e| {error!("Failed to send data {}", e);e})?;
    }

    Ok(())
}