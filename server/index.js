const SerialPort = require("serialport")//importar modulo para comunicacion serial
const mySerial = new SerialPort("COM18", {baudRate: 115200})//configuracion puerto y velocidad de transmision

//evento comunicacion serial arbierta
mySerial.on("open", function() {
    console.log("COMUNICACION SERIAL ABIERTA")
})

//escucha datos en buffer
mySerial.on("data", function (data) {
    console.log(data.toString())
})

//evento de error
mySerial.on("err", function(err) {
    console.log(err.message)
})