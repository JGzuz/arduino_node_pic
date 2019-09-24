const SerialPort = require("serialport")//importar modulo para comunicacion serial
const mySerial = new SerialPort("COM18", {baudRate: 115200})//configuracion puerto y velocidad de transmision

//declaracion de varaibles
var numArduino, numeroApto;

//evento comunicacion serial arbierta
mySerial.on("open", function() {
    console.log("COMUNICACION SERIAL ABIERTA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>OK")
    
})

//funcion para verificar si el numero esta en la base de datos y esta activo
function verificaNumero(cliente) {
    //console.log("------------------------------------------------------------------")
    //console.log(`Comarando el número ${numArduino}con:`)
    //console.log(`Número actual: ${cliente.numero}, estado: ${cliente.activo}`)
    if(cliente.numero === parseInt(numArduino)){
        console.log(`${cliente.numero} == ${numArduino}`)
        console.log(`El numero ${numArduino}se ha recargado exitosamente`)
        return true
    }
    
    //console.log("------------------------------------------------------------------")

}

//escucha datos en buffer
mySerial.on("data", function (data) {
    console.log(`Nuevo dato recibido: ${data.toString()}`)
    numArduino = data.toString()
    console.log(`Iniciando comparativa de: ${numArduino}`)
    numeroApto = clientes.filter(verificaNumero)
    //if(numeroApto != true){console.log("No hay recarga prro")}
    console.log("--------------------------------------")
})

//evento de error
mySerial.on("err", function(err) {
    console.log(err.message)
})



//basesita de datos falsos uwuwuwuw
var cliente1 = {
    nombre: "Juan",
    numero: 4661023845,
    id: "00000asdf1",
    activo: true,
    edad: 22
}

const cliente2 = {
    nombre: "Petra",
    id: "00000asdf1",
    activo: true,
    edad: 32,
    numero: 1334512345
}

const cliente3 = {
    nombre: "Luisa",
    numero: 1111111111,
    id: "00000asdf1",
    activo: true,
    edad: 28
}

const cliente4 = {
    nombre: "Brayan",
    numero: 2222222222,
    id: "00000asdf1",
    activo: true,
    edad: 59
}

const cliente5 = {
    nombre: "Steve",
    numero: 3333333333,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const clientes = [cliente1, cliente2, cliente3, cliente4, cliente5]
/////termino de basesita de datos


