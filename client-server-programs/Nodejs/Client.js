const net = require('net')
const readline = require('readline')

const PORT = PORT_NUM;
const HOST = 'IP_NUM';

const s = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: "Write the message you want to send \n"
});

const client = net.createConnection({port:PORT,host:HOST},function(){
    s.prompt();
});

client.on('error',function(error){
    console.error("Connection error: ",error.message);
});


s.on('line',function(line){
    client.write(line+'\n');
});

client.on('data',function(data){

try{
    console.log(data.toString());
    console.log("\n");
    s.prompt()
 }catch (e){
    console.error("Error handling data: ",e);
    }
   
});