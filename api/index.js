const coap = require('coap')
const server = coap.createServer()

server.on('request', (req, res) => {
  console.log("Request da");
  res.end('Hello ' + req.url.split('/')[1] + '\n')
})

server.listen(3000, () => {console.log("yoooo Server laufen tuen")});
