mod utils;
use utils::handle_client::handle_client;

use clap::Parser;
use std::net::TcpListener;
use std::error;
use log::{error,info,warn,debug,trace};


#[derive(Parser)]
struct Arguments{
    #[clap(long)]
    ip_and_port: String,
}

fn main() -> Result<(),Box<dyn error::Error>> {
    env_logger::init();

    let args = Arguments::parse();
    let server_socket = TcpListener::bind(&args.ip_and_port).map_err(|e| {error!("Failed to bind {}", e);e})?;
    info!("Sever started and is running successfully on {}",args.ip_and_port);

    
    let (stream,_) = server_socket.accept().map_err(|e| {error!("Failed to accept client {}", e);e})?;
    info!("Client accepted successfully!");
    handle_client(stream)?;

    Ok(())
}