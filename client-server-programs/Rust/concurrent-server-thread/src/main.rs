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
    env_logger::init();

    let args = Arguments::parse();
    let concurrent_server_socket = TcpListener::bind(&args.ip_and_port).map_err(|e| {error!("Failed to bind {}", e);e})?;
    info!("Concurrent server successfully started and running....");

    for incoming_request in concurrent_server_socket.incoming(){
       let client_stream = match incoming_request{
        Ok(stream) => stream,
        Err(e) => {
            error!("connection error {}",e);
            continue;
        } 
       };

       thread::spawn( move || {
        if let Err(e) = handle_client(client_stream) {
            error!("Error handling client: {:?}",e);
        }
       });
    }

    Ok(())
   
}
