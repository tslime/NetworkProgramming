use tokio::net::TcpStream;
use tokio::io::{AsyncReadExt,AsyncWriteExt};
use std::error;
use log::{error,warn,debug,info,trace};

pub async fn handle_client(mut client_stream: TcpStream) -> Result<(),Box<dyn error::Error>> {
    let mut buffer = [0;512];

    loop{
        let bytes_read = client_stream.read(&mut buffer).await?;
        if bytes_read == 0 {
            info!("Client disconnected");
            break;
        }

        let message = String::from_utf8_lossy(&buffer[..bytes_read]);
        info!("client message: {}",message);
        client_stream.write_all(b"Message received\n").await?;
        client_stream.flush().await?;
    }

    Ok(())
}