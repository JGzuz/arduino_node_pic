const SerialPort = require("serialport")//importar modulo para comunicacion serial
const mySerial = new SerialPort("COM18", {baudRate: 115200})//configuracion puerto y velocidad de transmision

//declaracion de varaibles
let numArduino, numeroApto;
let parteAnterior;

//evento comunicacion serial arbierta
mySerial.on("open", function() {
    console.log("COMUNICACION SERIAL ABIERTA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OK")
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
    console.log("<<<<<<-------------------------------------")
    console.log(`Nuevo dato recibido: ${data.toString()}`)
    numArduino = data.toString()
    console.log(`Iniciando comparativa de: ${numArduino}`)

    //verificar el tamaño del numero
    console.log(`Tamalo de cadena: ${numArduino.length}`)
    if(numArduino.length < 12){
        numArduino = parteAnterior + numArduino
        console.log(`nueva cadena: ${numArduino}`)
    }

    setTimeout(() => {
        numeroApto = clientes.filter(verificaNumero)
    }, 800)
    

    //if(numeroApto != true){console.log("No hay recarga prro")}
    
    console.log("-------------------------------------->>>>>")
})

//evento de error
mySerial.on("err", function(err) {
    console.log(err.message)
})



//basesita de datos falsos uwuwuwuw
var cliente1 = {
    nombre: "Juan",
    numero: 1000000000,
    id: "00000asdf1",
    activo: true,
    edad: 22
}

const cliente2 = {
    nombre: "Petra",
    id: "00000asdf1",
    activo: true,
    edad: 32,
    numero: 1000000001
}

const cliente3 = {
    nombre: "Luisa",
    numero: 1000000002,
    id: "00000asdf1",
    activo: true,
    edad: 28
}

const cliente4 = {
    nombre: "Brayan",
    numero: 1000000003,
    id: "00000asdf1",
    activo: true,
    edad: 59
}

const cliente5 = {
    nombre: "Steve",
    numero: 1000000004,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente6 = {
    nombre: "persona6",
    numero: 1000000005,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente7 = {
    nombre: "persona6",
    numero: 1000000006,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente8 = {
    nombre: "persona6",
    numero: 1000000007,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente9 = {
    nombre: "persona6",
    numero: 1000000008,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente10 = {
    nombre: "persona6",
    numero: 1000000009,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente11 = {
    nombre: "persona6",
    numero: 1000000010,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente12 = {
    nombre: "persona6",
    numero: 1000000011,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente13 = {
    nombre: "persona6",
    numero: 1000000012,
    id: "00000asdf1",
    activo: true,
    edad: 30
}


const clientes = [cliente1, cliente2, cliente3, cliente4, cliente5, cliente6, cliente7, cliente8, cliente9, cliente10, cliente11, cliente12, cliente13]
/////termino de basesita de datos


