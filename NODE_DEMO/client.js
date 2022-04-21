const coap = require('coap')
const req = coap.request({
  observe: false,
  host: 'localhost',
  pathname: '/',
  port: 3000,
  method: 'get',
  confirmable: 'true',
  retrySend: 'true',
  //query:'',
  options: {
    //  "Content-Format": 'application/json'
  }
})

//payload erstellen
var payload = {
    username: 'abdu',
}

//payload hinzufügen
req.write(JSON.stringify(payload));

//auf antword des servers reagieren
req.on('response', (res) => {
  res.pipe(process.stdout)
  res.on('end', () => {
    console.log("Auftrag erledigt")
    process.exit(0)
  })
})

//server anfrage senden
req.end()
  