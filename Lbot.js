/**
 * @description Importaçao de blibiotecas
 * 
 * @requires tmi.js
 * @requires fs
 * @requires request
 */
const tmi = require('tmi.js');
const fs = require('fs');
const request = require ('request');
const { SSL_OP_EPHEMERAL_RSA } = require('constants');
/**
 * @description Construção de Objetos
 */
const options = JSON.parse(fs.readFileSync('options.json'));

/**
 * @description Eventos (Funções Callback)
 * @throws Erro quando arduino não conectado corretamente
 */

	/**
	 * @description Configuração e Conexão com API da Twitch.TV
	 */
	const client = new tmi.client(options);
	client.connect();

	/**
	 * @description Quando menssagem enviada
	 * @see raw_message tem os dados brutos de qualquer evento de chat da live (messangem, highlight, host, raid)
	 */

	function delay(ms) {
		return new Promise(resolve => setTimeout(resolve, ms));
	  }

	client.on("raw_message", (messageCloned, message) => {
		//console.log(message);
		// ignorar quando não for uma menssagem no chat
		if (message.command != "PRIVMSG") {
			return;
		}

		// preparar para executar comandos
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
			case "rosa": 
				client.say (message.params[0],"Cenário bonito <3");
				request("http://192.168.0.120/Crimson");
				break;
			case "verde":
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
			}
	});