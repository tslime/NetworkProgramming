mod utils;
use utils::handle_client::handle_client;

use clap::Parser;
use std::net::TcpListener;
use std::thread;
use std::error;
use log::{error,info,warn,debug,trace};


#[derive(Parser)]
struct Arguments{
    #[clap(long)]
    ip_and_port: String,
}

fn main() -> Result<(),Box<dyn error::Error>> {
    env_logger.init();

    let concurrent_server_socket = TcpListener::bind("192.168.2.57:2222").map_err(|e| {error!("Failed to bind {}", e);e})?;
    info!("Concurrent server successfully started and running....");

    for incoming_request in concurrent_server_socket.incoming(){
       let mut client_stream = incoming_request.map_err(|e| {error!("Failed to accept client {}", e);e})?;
       thread::spawn( move || {
        handle_client(client_stream)?;
       });
    }

    Ok(())
   
}
