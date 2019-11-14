const SerialPort = require("serialport")//importar modulo para comunicacion serial
const Readline = SerialPort.parsers.Readline
const parser = new Readline()
const mySerial = new SerialPort("COM3", {baudRate: 19200})//configuracion puerto y velocidad de transmision


//declaracion de varaibles
let numArduino="", numeroApto, numOK2
let parteAnterior
let sub_bufer //bandera para iniciar el proceso de recarga
let numRecarga = []
let datoCliente = ""
let chargeNum, solicitaNum, fechaRecarga, recargaEste
let getMsn = 0 //bandera pa indicar que la siguinte informacion que se reciba es el texto del msn
let modOk = 0, initSim900 = 0// si initSim900=1 => modulo inicializado, si modOk=1 => cadena aux guarda msn 
let cadS9 = ""
let cadenaSec = ""//cadena que almacena una vez inicializado el nodulo
let concatenandoMsn = 0
let countRn = 0
let finMsn = 0
let textFull ="" //texto completo recibido por serie
let msnFull =""//para del msn completa, sin los datos de fecha y quien envia
let arrayPos = 0 //variable incremental para ver la posicion en que nos encontramos del array de clientes
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


//cuando el numero no se encuentra en la base de datos 
function NumNoBase(alNumero) {
    setTimeout(()=>{
        alNumero = "RB" + alNumero
        mySerial.write(alNumero)
        alNumero = ""
    }, 500)
}

//para cuando la recarga se realizo correctamente
function RecargaOk(enviarANumber) {
    setTimeout(()=>{
        enviarANumber = "RK" + enviarANumber
        mySerial.write(enviarANumber)
        enviarANumber = ""
    }, 500)
}

//para cuando el mensaje no es un numero de 10 digitos
function formatoIncorrecto(longMensaje, sendToNumber) {
    if(longMensaje.length <= 20){
        setTimeout(() => {
            //msn cuando el numero no viene en el formato correcto
            sendToNumber = "RS" + sendToNumber
            mySerial.write(sendToNumber)//sin formato, enviar msn al cliente
            //mySerial.write()
            sendToNumber = ""
        }, 500)
    }

    if(longMensaje.length > 20){
        setTimeout(() => {
            mySerial.write("sf_sin_msn")
        }, 500)
    }
    
}



//evento comunicacion serial arbierta
mySerial.on("open", function() {
    console.log("COMUNICACION SERIAL ABIERTA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OK")
    //cadenas();
})

//filtra el numero para comprovar si esta en basesita
async function recargaNum(recargaEsteNum, sendAEsteNum) {
    arrayPos = 0
    return new Promise((resolve, reject)=>{
        setTimeout(()=>{
            resolve(numOK2 = clientes.filter(verificaNumero))
        },500)
    })
}


//funcion para verificar si el numero esta en la base de datos
function verificaNumero(cliente) {//numArduino =>
    
    if(cliente.numero === parseInt(chargeNum)){
        console.log(`Se encontro una coincidencia: ${cliente.numero} == ${chargeNum}`)
        RecargaOk(solicitaNum)
        setTimeout(()=>{
            console.log(`El numero ${chargeNum} se ha recargado exitosamente`)
            console.log(`>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>END`)
        },500)
    }
    else{
        arrayPos++
        if(arrayPos == clientes.length){
            NumNoBase(solicitaNum)
            console.log("El numero no se encontro en la base de datos")
            console.log(`>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>END`)
        }
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

//funcion para buscar el numero a recargar 
function targetNum(parteTex){

let num10Dig = false //para validar que sea un numero de 10 digitos
let numPos11 = false //para validar que el numero no sea de mas de 10 digitos
let posInit = 0, posEnd = 0 //para determinar la subcadena con el numero de 10 digitos 
let esNumero = false
let numFound //el numero de 10 digitos en el formato correcto
let aislarNum = ""
    console.log("buscando numero...")
    console.log(isNaN("4R5"))
    console.log(isNaN("R"))
    console.log(isNaN("455 "))
    console.log(isNaN(" 455"))
    console.log(isNaN("234 345"))
    console.log(isNaN("5"))
    console.log(isNaN(" "))
    for(let posAct=0; posAct <= (parteTex.length)-3; posAct++ )
    {
        //segmento de 10 digitos detectados
        if((parteTex.charAt(posAct) != " ") && (!isNaN(parteTex.charAt(posAct)))){
            console.log(`posicion ${posAct}: ${parteTex.charAt(posAct)}`)
            aislarNum = parteTex.substr(posAct,posAct+9)
                if(!isNaN(aislarNum)){
                    console.log(`numero: ${aislarNum}`)
                }
        }//fin de detectar segmento de 10 digitos
    }

}//fin de funcion de encontrar un numero en el formato adecuado: 10 digitos solos

//separa el mensaje en numero que solicita la recarga, numero al que se desea hacer la recarga, la
//fecha de recarga, *tambien ponerle que verifique si si es un mensaje
function Seccionador(mensaje) {

    fechaRecarga = mensaje.substr((mensaje.indexOf('+') + 23),20)
    console.log(`Fecha de solitud: ${fechaRecarga}`)

    solicitaNum = mensaje.substr((mensaje.indexOf('+') + 7),10)
    console.log(`Número que solicita: ${solicitaNum}`)

    chargeNum = mensaje.substr((mensaje.indexOf('+') + 46),10)
    //console.log(`tamaño número ${chargeNum.length}`)
    console.log(`Número a recargar: ${chargeNum}`)

    msnFull = mensaje.substr((mensaje.indexOf('+') + 46),(mensaje.length))

    //verifica que sea un numero de 10 digitos, si los es procede al proceso de recarga
    if(!isNaN(chargeNum) && (chargeNum.length == 10)){//si es un numero 
        recargaNum(chargeNum, solicitaNum)
    }

    if(isNaN(chargeNum) || chargeNum.length < 10){//cuando no es un numero o no esta en el formato correcto
        //aqui necesito agregarle la condicion que solo lo mande cuando el tamaño del msn
        //no excede cierto tamaño
        console.log("Formato incorrecto de numero, solo envie un numero de 10 digitos")
        console.log("sin espacios ni otro tipo de caracteres")
        console.log(`>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>END`)
        formatoIncorrecto(msnFull, solicitaNum)
    }
    

    /*
    textFull = mensaje.substr((mensaje.indexOf('+') + 46), (mensaje.lenth))
    console.log(`Texto individual ${textFull}`)
    targetNum(textFull)*/
    //mySerial.write('AT+GSN')
    
    
}

//escucha datos en buffer
mySerial.on("data", function (data) {
    //console.log(`Nuevo dato recibido: ${data.toString()}`)//descomentar para ver el dato recibido
    //console.log(`Tamaño: ${numArduino.length}`)

    numArduino = data.toString()//guardamos en una variable lo que se recibio por el puerto serie
    //console.log(`Acumulado en la cadena: ${cadS9}`)
    //console.log(`Acumulado en datocliente: ${datoCliente}`)

    //acumula en cadena para comprobar inicializacion del modulo
    if(initSim900 == 0){//si el modulo sim900 no ha inicializado
        cadS9 = cadS9 + numArduino
        //console.log(`Esto hay en el buffer ahora: ${cadS9}`) //para ver lo acumulado en la cadena

            //para verificar cuando el modulo se haya inicializado
             if(cadS9.indexOf("CMGF=") >= 0){
                setTimeout(()=>{
                console.log(`MODULO INICIALIZADO >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OK`)
                },1000)
                cadS9 = ""//limpiamos la cadena para que no entre constantamente aqui
                initSim900 = 1 // el modulo se ha inicializado
             }   
    }

    //almacena datos de puerto serie, esta cadena ya almacena un msn recidibo
    //el msn entero
    if(concatenandoMsn == 1){
        datoCliente = datoCliente + numArduino
        //console.log(`Esto tiene datoCliente: ${datoCliente}`)
        //console.log(`tamaño cadena anterior: ${datoCliente.length}`)

        /*
        chargeNum = mensaje.substr((mensaje.indexOf('+') + 46),10)
        console.log(`Número a recargar: ${chargeNum}`)
        if(datoCliente.indexOf("\u000A") >= 0){
            console.log("ya entro al salto de linea")
            countRn++
            console.log(countRn)
        }*/
        if(datoCliente.indexOf('\u000A',(datoCliente.indexOf('+') + 46 )) >= 0 ){
            //console.log("posicion del ultimo saldo de liena")
            console.log(datoCliente.indexOf('\u000A',(datoCliente.indexOf('+') + 46 )))
            finMsn = 1
        }
        
        if(finMsn === 1){
            
            console.log(`NUEVO MSN START PROCESS................................................`)
            console.log(`${datoCliente}`)
            Seccionador(datoCliente)
            concatenandoMsn=0
            datoCliente = ""
            finMsn = 0
        }
    }//fin rutina de almacenar msn entero

    //cadena que almacena una vez inicializado el modulo
    if((initSim900 == 1) && (concatenandoMsn == 0)){
        cadenaSec = cadenaSec + numArduino //almacena los datos que llegan por serie en esta cadena
        if(cadenaSec.indexOf("+CMT:") >=0 ){//si encuntras este segemento en la dacadena
            concatenandoMsn = 1 //para iniciar a guardar lo que llega
            datoCliente = cadenaSec.substr(cadenaSec.indexOf('+CMT:'),cadenaSec.lenth)//almacenamos a partir de +CMT: hata el tamaño total
            //console.log(`Esto pasó a datosCliente: ${datoCliente}`)
            cadenaSec = ""
        }
    }

    //espera a recibir un '+CMT:' para identificar que es un SMS 
    if(cadS9.indexOf("+CMT:123") >= 0){
        console.log(cadS9.indexOf("+CMT:")) //para ver cuando llega un nuevo sms
        concatenandoMsn = 1
        datoCliente = cadS9.substr(cadS9.indexOf('+CMT:'),cadS9.lenth)
        console.log(`Esto pasa a datosCliente: ${datoCliente}`)
        cadS9 = ""
        /*
        datoCliente = cadS9.substr(cadS9.indexOf('+CMT:'),cadS9.length)
        console.log(datoCliente)*/
    }

})//FIN DE RUTINA DE LECTURA DEL PUERTO SERIAL

//evento de error
mySerial.on("err", function(err) {
    console.log(err.message)
})



//basesita de datos falsos uwuwuwuw
var cliente1 = {
    nombre: "Juan",
    numero: 4443332211,
    id: "00000asdf1",
    activo: true,
    edad: 22
}

const cliente2 = {
    nombre: "Petra",
    id: "00000asdf1",
    activo: true,
    edad: 32,
    numero: 4661071837
}

const cliente3 = {
    nombre: "Luisa",
    numero: 5552221144,
    id: "00000asdf1",
    activo: true,
    edad: 28
}

const cliente4 = {
    nombre: "Brayan",
    numero: 7776662233,
    id: "00000asdf1",
    activo: true,
    edad: 59
}

const cliente5 = {
    nombre: "Steve",
    numero: 8885552233,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente6 = {
    nombre: "persona6",
    numero: 7779992211,
    id: "00000asdf1",
    activo: true,
    edad: 30
}

const cliente7 = {
    nombre: "persona6",
    numero: 9879874473,
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


