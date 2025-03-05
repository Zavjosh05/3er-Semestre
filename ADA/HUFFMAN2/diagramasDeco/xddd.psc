Función addACadenaUnsigned(arrayAgegar,charAgregr,taArreglo)
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
FinFunción

Función Salir(ele) // Añade el terminador nulo
	
FinFunción

// Declaraciones vacías para funciones auxiliares
Función res <- CrearCadena(tamano)
	// Simula la asignación de memoria dinámica
FinFunción

Función res <- RedimensionarCadena(original,nuevoTamano)
	// Simula la redimensión de una cadena (como realloc)
FinFunción

Función res <- cadenaDeBitsIguales(cadenaDeBitsRecibida,arrayCaracteres,tamArrayCaracteres,bitCoincidencia)
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
FinFunción

// Declaraciones vacías para funciones auxiliares
Función res <- Largo(c)
	// Devuelve la longitud de la cadena
FinFunción

Función res <- tamArrayCharUnsigned(adena)
	// Calcula el tamaño de la cadena en formato unsigned
FinFunción

Algoritmo xddd
	
FinAlgoritmo
