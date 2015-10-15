//  LED-Painter, to draw live on a LED-Matrix
//  Copyright (C) 2015 Dominik Meier(XPerianer)
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  E-Mail: Hiscore.pressthebutton@hotmail.de



// Creating a TCP-Receiver
var tcp_client = 0;
var WebSocketServer = require('ws').Server
var DataGetter = new WebSocketServer({host: '0.0.0.0',port:8000});
DataGetter.on('connection',function(ws){


	console.log("Client(Painter) mit Websocket verbunden");

	ws.on('message',function(message){ //(empfängt nachrichten)
		//console.log('Von Websocket-Client empfangen: ' + message);
		if(tcp_client != 0 && message.charAt(0) == '['){ //Very dirty way of checking if it's actually a fine message from the Painter(this is because it would sende a Client connected message if this wasn't checked)
		tcp_client.write(message);
		//console.log(message);
		};
	});

	ws.on('close',function(){
		ws.close();
	});


});

var net = require('net');

var DataSender = net.createServer(function (socket){
		tcp_client = socket;
		console.log("Client(DataSender) connected")
		socket.on('error',function(data){
			tcp_client = 0;
			console.log("Socket has thrown an error: " + data);
		});
		socket.on('close',function(data){
			tcp_client = 0;
			console.log("Client(DataSender) disconnected")
		});
});
DataSender.listen(1337,'0.0.0.0');


//Auslieferung der Webfiles
var connect = require('connect'),
    serveStatic = require('serve-static');

var app = connect();

app.use(serveStatic("webfiles/"));
app.listen(80);
