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


var payload = {
    username: 'aniu',
}

req.on('response', (res) => {
  res.pipe(process.stdout)
  res.on('end', () => {
    console.log("Auftrag erledigt")
    process.exit(0)
  })
})

req.end()
  