mod utils;
use utils::handle_client::handle_client;

use tokio::net::TcpListener;

#[tokio::main]
async fn main() {

    let concurrent_async_socket = TcpListener.bind("192.168.2.57:2222").await().expect("failed to bind address!\n\n");
    println!("Concurrent server listenting at port 2222.....\n\n");
}
