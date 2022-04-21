const coap = require('coap')
const server = coap.createServer()

//server reagiert auf request (Anfrage)
server.on('request', (req, res) => {
  //zeigen das eine Anfrage angekommen ist und payload anzeigen
  console.log('Request da. Payload: ' + req.payload);

  //eine Antwort mit dem Payload zurücksenden
  res.end('Hello Welt ' +  req.payload+ '\n')
})

//Server online stellen
server.listen(process.env.PORT || 3000, () => {console.log("Server läuft")});
