use std::net::TcpStream;
use std::io::{Read,Write};
use std::error;
use log::{error,info,warn,debug,trace};

pub fn handle_client(mut client_stream: TcpStream) -> Result<(),Box<dyn error::Error>> {
    let mut buffer = [0;512];

    loop{
        let bytes_read = client_stream.read(&mut buffer)?;
         if bytes_read == 0 {
            info!("client disconnected!");
            break;
        }

        let message = String::from_utf8_lossy(&buffer[..bytes_read]);
        info!("client message: {}",message);
        client_stream.write_all(b"Message received\n")?;
        client_stream.flush()?;
    }

    Ok(())
}