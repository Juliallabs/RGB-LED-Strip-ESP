
const tmi = require('tmi.js');
const fs = require('fs');
const request = require ('request');
const { SSL_OP_EPHEMERAL_RSA } = require('constants');

const options = JSON.parse(fs.readFileSync('options.json'));

const client = new tmi.client(options);
client.connect();


function delay(ms) {
	return new Promise(resolve => setTimeout(resolve, ms));
}

client.on("raw_message", (messageCloned, message) => {

	if (message.command != "PRIVMSG") {
		return;
	}


	let is_highlight = message.tags["msg-id"] == 'highlighted-message';
	let channel = message.params[0];
	let params = message.params[1].slice(1).split(' ');
	let command = params.shift().toLowerCase(); 
    let reward = message.tags["custom-reward-id"];
	console.log(command);
	if (reward == "b1c95eb2-6154-4a99-8ead-042d0d52e133") {
		request("http://192.168.0.120/hydrabot");	
		delay(10000);
		request("http://192.168.0.120/Roxinha");

	}
	switch (command){
		case "rosa": -
			client.say (message.params[0],"Cenário bonito <3");
			request("http://192.168.0.120/Crimson");
			break;
		case "turqueza":
			client.say (message.params[0],"Cenário bonito verdinho <3");
			request("http://192.168.0.120/Lime");
			break;
		case "amarelo":
			client.say (message.params[0],"Cenário bonito <3");
			request("http://192.168.0.120/Amarelo");
			break;
		case "laranja":
			client.say (message.params[0],"Cenário bonito <3");
			request("http://192.168.0.120/Laranja");
			break;
		case "roxo":
			client.say (message.params[0],"Cenário bonito <3");
			request("http://192.168.0.120/Roxinha");
			break;
		case "vermelho":
			client.say (message.params[0],"Cenário bonito <3");
			request("http://192.168.0.120/Vermelho");
			break;
		case "azul":
			client.say (message.params[0],"Cenário bonito <3");
			request("http://192.168.0.120/Turquoise");
			break;
		case "ciano":
			client.say (message.params[0],"TOMA O TEU CIANO julial9Wtf ");
			request("http://192.168.0.120/Ciano");
			break;
		case "brancoclaro":
			client.say (message.params[0],"legal essa cor julial9Wtf ");
			request("http://192.168.0.120/caquinha");
			break;
		case "brancoescuro":
			client.say (message.params[0],"legal essa cor julial9Wtf ");
			request("http://192.168.0.120/off");
			break;
		case "verde":
			client.say (message.params[0],"Cenário bonito verdinho <3");
			request("http://192.168.0.120/Verde");
			break;
		}
	});