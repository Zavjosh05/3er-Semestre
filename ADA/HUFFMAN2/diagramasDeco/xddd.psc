Funci�n addACadenaUnsigned(arrayAgegar,charAgregr,taArreglo)
	Definir temp Como Cadena
	Si tamArreglo=0 Entonces
		tamArreglo <- tamArreglo+1
		arrayAAgregar <- CrearCadena(tamArreglo+1)
		Si arrayAAgregar=NULL Entonces
			Salir(-1) // Reserva memoria
		FinSi
		arrayAAgregar <- charAAgregar
	SiNo
		tamArreglo <- tamArreglo+1
		temp <- arrayAAgregar
		arrayAAgregar <- RedimensionarCadena(temp,tamArreglo+1)
		Si arrayAAgregar=NULL Entonces
			Salir(-1)
		FinSi
		arrayAAgregar <- charAAgregar
	FinSi
	arrayAAgregar <- '\0'
FinFunci�n

Funci�n Salir(ele) // A�ade el terminador nulo
	
FinFunci�n

// Declaraciones vac�as para funciones auxiliares
Funci�n res <- CrearCadena(tamano)
	// Simula la asignaci�n de memoria din�mica
FinFunci�n

Funci�n res <- RedimensionarCadena(original,nuevoTamano)
	// Simula la redimensi�n de una cadena (como realloc)
FinFunci�n

Funci�n res <- cadenaDeBitsIguales(cadenaDeBitsRecibida,arrayCaracteres,tamArrayCaracteres,bitCoincidencia)
	Definir tamCadenaBit, yz, z, tamCadena, j Como Entero
	Definir cadenaDeBits Como Cadena
	// Calcula la longitud de la cadena recibida
	tamCadenaBit <- Largo(cadenaDeBitsRecibida)
	Para i<-0 Hasta tamArrayCaracteres-1 Hacer
		yz <- 0
		z <- tamCadena
		// Si las longitudes no coinciden, salta al siguiente elemento
		Si z<>tamCadenaBit Entonces
		
		FinSi
		j <- 0
		// Compara cada bit de las cadenas
		Mientras (cadenaDeBitsRecibida<>'0') Hacer
			Si cadenaDeBitsRecibida=cadenaDeBits Entonces
				yz <- yz+1
			SiNo
				yz <- 0
			FinSi
			// Si hay coincidencia exacta
			Si yz=tamArrayCharUnsigned(cadenaDeBits) Entonces
				bitCoincidencia <- elem
			FinSi
		FinMientras
	FinPara
FinFunci�n

// Declaraciones vac�as para funciones auxiliares
Funci�n res <- Largo(c)
	// Devuelve la longitud de la cadena
FinFunci�n

Funci�n res <- tamArrayCharUnsigned(adena)
	// Calcula el tama�o de la cadena en formato unsigned
FinFunci�n

Algoritmo xddd
	
FinAlgoritmo
