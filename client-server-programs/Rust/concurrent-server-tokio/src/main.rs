mod utils;
use utils::handle_client::handle_client;

use clap::Parser;
use tokio::net::TcpListener;
use std::error;
use log::{error,warn,debug,info,trace};


#[derive(Parser)]
struct Arguments{
    #[clap(long)]
    ip_and_port: String
}

#[tokio::main]
async fn main() -> Result<(),Box<dyn error::Error>> {
    env_logger::init();

    let args = Arguments::parse();
    let concurrent_async_socket = TcpListener::bind(&args.ip_and_port).await?;
    info!("Concurrent server listenting at port 2222.....\n\n");

    loop{
        let (client_stream, address) = match concurrent_async_socket.accept().await {
            Ok((stream,addr)) => (stream, addr),
            Err(e) => {
                error!("Connection failed: {}",e);
                continue;
            }
        };
        
        tokio::spawn(async move {
            if let Err(e) = handle_client(client_stream).await {
                error!("Error handling client {}",e);
            }
        });
    }
}
