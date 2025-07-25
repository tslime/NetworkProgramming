const net = require('net');
let c_num = 0;

const PORT = 6379;
const HOST = '192.168.2.57';

const server = net.createServer(function(socket){
    console.log('New connection.....');
    c_num++;
    socket.clientid = c_num;

    socket.on('data',function(data){
     try{
        console.log("Client ",socket.clientid," says: ", data.toString());
        socket.write("Message received \n");
     }catch(e){
        console.error("Error handling data: ",e);
     }
        
    
    });
});

server.listen(PORT,HOST);

server.on('error',function(error){
    console.error("Server error: ",error.message);
});