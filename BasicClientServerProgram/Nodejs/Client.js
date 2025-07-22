const net = require('net')
const readline = require('readline')

const PORT = 6379;
const HOST = '192.168.2.57';

const client = net.createConnection({port:PORT,host:HOST},function(){
    s.prompt();
});


const s = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: "Write the message you want to send \n"
});


s.on('line',function(line){
    client.write(line+'\n');
});

client.on('data',function(data){
    console.log(data.toString());
    console.log("\n");
    s.prompt()
});