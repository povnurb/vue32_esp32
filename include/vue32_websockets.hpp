

// -------------------------------------------------------------------
// Declaración de funciones de request
// -------------------------------------------------------------------
void ProcessRequest(AsyncWebSocketClient * client, String request);

// -------------------------------------------------------------------
// Variable para tiempo de envio por WS
// -------------------------------------------------------------------
long lastWsSend = 0;    

// -------------------------------------------------------------------
// manejor de Eventos del Websocket de la libreria
// -------------------------------------------------------------------
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){ 
	if(type == WS_EVT_CONNECT){
		Serial.printf("[ INFO ] ws[%s][%u] connect\n", server->url(), client->id());
		client->printf("{\"ClientID\": %u }", client->id());  //muestra el id del cliente
		client->ping();  //para mantener la conexion
	} else if(type == WS_EVT_DISCONNECT){
		//Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
	} else if(type == WS_EVT_ERROR){
		//Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
	} else if(type == WS_EVT_PONG){
		//Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
	} else if(type == WS_EVT_DATA){  //cuando llega una data
		AwsFrameInfo * info = (AwsFrameInfo*)arg;
		String msg = "";
		if(info->final && info->index == 0 && info->len == len){
			if(info->opcode == WS_TEXT){
				for(size_t i=0; i < info->len; i++) {
					msg += (char) data[i];
				}
			} else {
				char buff[3];
				for(size_t i=0; i < info->len; i++) {
					sprintf(buff, "%02x ", (uint8_t) data[i]);
					msg += buff ;
				}
			}
			if(info->opcode == WS_TEXT)
			   ProcessRequest(client, msg);			
		} else {
			//message is comprised of multiple frames or the frame is split into multiple packets
			if(info->opcode == WS_TEXT){
				for(size_t i=0; i < len; i++) {
					msg += (char) data[i];
				}
			} else {
				char buff[3];
				for(size_t i=0; i < len; i++) {
					sprintf(buff, "%02x ", (uint8_t) data[i]);
					msg += buff ;
				}
			}
			Serial.printf("%s\n",msg.c_str());

			if((info->index + len) == info->len){
				if(info->final){
					if(info->message_opcode == WS_TEXT)
					   ProcessRequest(client, msg);
				}
			}
		}
	}
}
// -------------------------------------------------------------------
// Inicializar el Websocket
// -------------------------------------------------------------------
void InitWebSockets(){
	ws.onEvent(onWsEvent);
	server.addHandler(&ws);
    log("[ INFO ] Servidor WebSocket iniciado");
}
// -------------------------------------------------------------------
// Manejador de ordenes enviada por Websocket
// -------------------------------------------------------------------
void ProcessRequest(AsyncWebSocketClient * client, String request){    
	String command = request;
    command.trim();
    }/*
	if (strcmp(command.c_str(), "restore") == 0){
		log("[ INFO ] Commando por WS => " + command);
		settingsReset();
		if(settingsSave()){
			WsMessage("¡Equipo restablecido correctamente!","undo-alt","info");
			log("[ INFO ] ¡Equipo restablecido correctamente!");
			Serial.flush(); 
			ESP.restart();
		}
	}else if(strcmp(command.c_str(), "restart") == 0){
		log("[ INFO ] Commando por WS => " + command);	
		WsMessage("¡Equipo reiniciado correctamente!","redo-alt","info");
		log("[ INFO ] ¡Equipo reiniciado correctamente!");
		Serial.flush(); 
		ESP.restart();
	}
	
}*/
// -------------------------------------------------------------------
// Función enviar JSON por Websocket 
// -------------------------------------------------------------------
void WsMessage(String msg, String icon, String Type){
	if(Type == "msg"){
	/*if(strcmp(Type.c_str(), "info") == 0){
		String response;
		StaticJsonDocument<300> doc;
		doc["type"] = Type;
		doc["msg"] = msg;
		doc["icon"] = icon;
		serializeJson(doc, response);
		ws.textAll(response);
		*/
	}else{
		ws.textAll(msg);
	}
	
}/*
// -------------------------------------------------------------------
// Empaquetar el JSON para enviar por WS Datos para Index cada 1s
// -------------------------------------------------------------------
String getJsonIndex(){
	String response = "";
	DynamicJsonDocument jsonDoc(3000);
	jsonDoc["type"] = "data";
	jsonDoc["device_time_active"] = longTimeStr(millis() / 1000);
	jsonDoc["device_ram_available"] = ESP.getFreeHeap();
	jsonDoc["mqtt_online"] = mqttClient.connected() ? true : false;
	jsonDoc["mqtt_server"] = mqttClient.connected() ? F(mqtt_server) : F("server not connected");
	jsonDoc["wifi_online"] = WiFi.status() == WL_CONNECTED ? true : false;
	jsonDoc["wifi_rssi"] = WiFi.status() == WL_CONNECTED ? WiFi.RSSI() : 0;
	jsonDoc["wifi_signal"] = WiFi.status() == WL_CONNECTED ? getRSSIasQuality(WiFi.RSSI()) : 0;
	serializeJson(jsonDoc, response);
	return response;
}
*/

