const SerialPort = require("serialport")//importar modulo para comunicacion serial
const Readline = SerialPort.parsers.Readline
const parser = new Readline()
const mySerial = new SerialPort("COM18", {baudRate: 115200})//configuracion puerto y velocidad de transmision


//declaracion de varaibles
let numArduino="", numeroApto, numOK2
let parteAnterior
let sub_bufer //bandera para iniciar el proceso de recarga
let numRecarga = []
let datoCliente
let chargeNum, clienteNum, fechaRecarga
let getMsn = 0 //bandera pa indicar que la siguinte informacion que se reciba es el texto del msn

//mandar datos a arduino
/*
function enviaDato() {
    mySerial.write('ATC_WRITE')
    //mySerial.write(Buffer.from('H'))
    console.log("led encendido...")
    
}*/
/*
//funcion para enviar una lista de numeros
function listarNumeros(lista){
    for(let i=0; i<=lista.length; i++){
        numArduino = lista[i]
        numOK2 = clientes.filter(verificaNumero)
    }
}*/



function cadenas() {
    
    setTimeout(() => {
        mySerial.write('ATC_ON') 
    },10000)
    setTimeout(()=>{
        mySerial.write('ATC_OFF')
    },15000)
    
   
}

function enviaMsn() {
    setTimeout(()=>{
        mySerial.write('MSN_ENVIADO')
    }, 500)
}

//evento comunicacion serial arbierta
mySerial.on("open", function() {
    console.log("COMUNICACION SERIAL ABIERTA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OK")
    //cadenas();
})

//filtra el numero para comprovar si esta en basesita
async function recargaNum(numArduino) {
    return new Promise((resolve, reject)=>{
        setTimeout(()=>{
            resolve(numOK2 = clientes.filter(verificaNumero))
        },3000)
    })
}

//funcion para verificar si el numero esta en la base de datos
function verificaNumero(cliente) {//numArduino =>
    if(cliente.numero === parseInt(numArduino)){
        console.log(`Se encontro una coincidencia: ${cliente.numero} == ${numArduino}`)
        enviaMsn()
        setTimeout(()=>{
            console.log(`El numero ${numArduino}se ha recargado exitosamente`)
        },2000)

        numeroArduino = ""
        
        console.log("------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        
        return true
    }
}

function seccionar(datos) {
    let numDeCliente
    let numARecargar
    numDeCliente = datos.substr(5,10)
    console.log(`Numero de cliente: ${numDeCliente}`)
    numARecargar = datos.substr(45,10)
    console.log(`Numero a recargar: ${numARecargar}`)
}



//escucha datos en buffer
mySerial.on("data", function (data) {
    console.log("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<----------------")
    console.log(`Nuevo dato recibido: ${data.toString()}`)
    //console.log(`Tamaño: ${numArduino.length}`)
    //analicis del dato 
    numArduino = data.toString()
    datoCliente = numArduino.substr(0,5)
    
    if(getMsn === 1){
        console.log(`Texto del mensaje: `)
    }

    if((numArduino.length < 50) && (sub_bufer === 1)){
        numArduino = parteAnterior + data.toString()
        console.log(`Nueva cadena concatenada: ${numArduino}`)
        console.log(`Nuevo tamaño: ${numArduino.length}`)
        clienteNum = numArduino.substr(7,10)
        fechaRecarga = numArduino.substr(23,20)
        //chargeNum = numArduino.substr(45, numArduino.length)
        console.log(`Numero que solicita: ${clienteNum}`)
        console.log(`fecha de solicitud: ${fechaRecarga}`)
        //console.log(`Numero a recargar: ${chargeNum}`)

        sub_bufer = 0
        getMsn = 1
        parteAnterior = "undefined"
    }
    if((numArduino.length < 50) && (datoCliente === "+CMT:")){
        console.log(`Nueva recarga en proceso ${datoCliente}`)
        parteAnterior = numArduino
        sub_bufer = 1
        console.log(`Primera parte de cadena: ${numArduino}`)
      }

})//FIN DE RUTINA DE LECTURA DEL PUERTO SERIAL


//evento de error
mySerial.on("err", function(err) {
    console.log(err.message)
})



//basesita de datos falsos uwuwuwuw
var cliente1 = {
    nombre: "Juan",
    numero: 1111111111,
    id: "00000asdf1",
    activo: true,
    edad: 22
}

const cliente2 = {
    nombre: "Petra",
    id: "00000asdf1",
    activo: true,
    edad: 32,
    numero: 1000000020
}

const cliente3 = {
    nombre: "Luisa",
    numero: 1000000030,
    id: "00000asdf1",
    activo: true,
    edad: 28
}

const cliente4 = {
    nombre: "Brayan",
    numero: 1000000040,
    id: "00000asdf1",
    activo: true,
    edad: 59
}

const cliente5 = {
    nombre: "Steve",
    numero: 1000000050,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente6 = {
    nombre: "persona6",
    numero: 1000000060,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente7 = {
    nombre: "persona6",
    numero: 1000000070,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente8 = {
    nombre: "persona6",
    numero: 1000000080,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente9 = {
    nombre: "persona6",
    numero: 1000000090,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente10 = {
    nombre: "persona6",
    numero: 1000000091,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente11 = {
    nombre: "persona6",
    numero: 1000000092,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente12 = {
    nombre: "persona6",
    numero: 1000000093,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente13 = {
    nombre: "persona6",
    numero: 1000000094,
    id: "00000asdf1",
    activo: true,
    edad: 30
}


const clientes = [cliente1, cliente2, cliente3, cliente4, cliente5, cliente6, cliente7, cliente8, cliente9, cliente10, cliente11, cliente12, cliente13]
/////termino de basesita de datos


