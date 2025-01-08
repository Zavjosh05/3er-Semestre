"""
3BM2

PROYECTO C. ANÁLISIS DE IMÁGENES CON TRANSFORMADA DE FOURIER
Profesor: David Coyac Correa

Vazquez Sanchez Omar Jesus
Vega Cortez Jose Angel
Zavaleta Guerrero Joshua Ivan
"""

import os #Librería para el manejo de rutas.
import tkinter as tk #Librería para interfaces gráficas.
from tkinter import filedialog #Abre cuadros de diálogo para cargar archivos. (En nuestro caso, la imágen)
from tkinter import simpledialog #Para cuadros de diálogo diversos.
from tkinter import messagebox #Abre cuadros de diálogo para avisos.
import cv2 #Librería para el procesamiento de imágenes.
import numpy as np #Librería para los calculos numéricos.
import matplotlib.pyplot as plt #Librería para la creación de gráficas, el módulo pyplot es para crear gráficos y visualizar datos.
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg  #FigureCanvasTkAgg sirve para integrar matplotlib con tkinter.
from matplotlib.figure import Figure #Para la creación de figuras.

class Fourier:
    def __init__(self, root):
        #Propiedades generales de la ventana.
        self.root = root  # Este constructor inicializa el objeto con el parámetro root. (La ventana principal de la aplicación)
        self.root.title("Trucha Inc. - Análisis de Imágenes con Transformada de Fourier (©2025)") #Título de la ventana.
        self.root.state("zoomed") #El programa inicia en pantalla completa.
        self.root.configure(bg="gray8") #Fondo oscuro pero no negro.

        #Configuración del ícono de la aplicación.
        script_dir = os.path.dirname(os.path.abspath(__file__))  # La ruta de este archivo.
        icon_path = os.path.join(script_dir, "../images/fish.ico") #Vuelve atrás una carpeta y entra a la que contiene el ícono.
        self.root.iconbitmap(icon_path) #Coloca el ícono en su lugar.

        #Título de la aplicación.
        self.showTitle = tk.Label(root, text="ANÁLISIS DE IMÁGENES CON TRANSFORMADA DE FOURIER", bg="gray8", fg="white", font=("Times New Roman", 35, "bold"))
        self.showTitle.place(x=60, y=30) #Establece la posición del título y deja su tamaño por defecto.

        #BOTONES DE MANEJO.

        #El botón cargar llama a la función "loadPicture" que permite cargar una imágen al programa.
        self.btnCargar = tk.Button(root, text="CARGAR", bg="gray20", fg="white", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.loadPicture)
        self.btnCargar.place(x=50, y=110, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón guardar llama a la función "savePicture" que permite cargar una imágen al programa.
        self.btnGuardar = tk.Button(root, text="GUARDAR", bg="gray20", fg="light green", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.savePicture)
        self.btnGuardar.place(x=50, y=200, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón eliminar llama a la función "deletePicture" que permite cargar una imágen al programa.
        self.btnEliminar = tk.Button(root, text="ELIMINAR", bg="gray20", fg="red", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.deletePicture)
        self.btnEliminar.place(x=50, y=290, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón umbral llama a la función "setUmbral" que permite cambiar el umbral de ondas para los filtros pasa-altas y pasa-bajas.
        self.btnUmbral = tk.Button(root, text="UMBRAL", bg="gray20", fg="white", font=("Times New Roman", 15, "italic"), borderwidth="2", relief="raised", command=self.setUmbral)
        self.btnUmbral.place(x=980, y=790, width=100) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón ancho llama a la función "setAncho" que permite cambiar el ancho para el filtro elimina-banda.
        self.btnAncho = tk.Button(root, text="ANCHO", bg="gray20", fg="white", font=("Times New Roman", 15, "italic"), borderwidth="2", relief="raised", command=self.setAncho)
        self.btnAncho.place(x=870, y=790, width=100) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón centro llama a la función "setCentro" que permite cambiar las coordenadas del centro para el filtro elimina-banda.
        self.btnCentro = tk.Button(root, text="CENTRO", bg="gray20", fg="white", font=("Times New Roman", 15, "italic"), borderwidth="2", relief="raised", command=self.setCentro)
        self.btnCentro.place(x=760, y=790, width=100)  #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón salir destruye la ventana principal y cierra el programa.
        self.btnSalir = tk.Button(root, text="SALIR", bg="gray20", fg="white", font=("Times New Roman", 15, "italic"), borderwidth="2", relief="raised", command=self.root.destroy)
        self.btnSalir.place(x=1415, y=790, width=100) #Esto solo establece la posición del botón y el tamaño del ancho.

        #BOTONES DE FILTRO.

        #El botón original llama a la función "showOriginal" que muestra la imágen original en escala de grises.
        self.btnOriginal = tk.Button(root, text="ORIGINAL", bg="gray20", fg="white", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.showOriginal)
        self.btnOriginal.place(x=50, y=400, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón espectro llama a la función "showEspectro" que muestra el espectro de frecuencias de la imágen.
        self.btnEspectro = tk.Button(root, text="ESPECTRO", bg="gray20", fg="white", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.showEspectro)
        self.btnEspectro.place(x=50, y=490, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón pasa-bajas llama a la función "showPasaBajas" que muestra la imágen después del filtro pasa-bajas.
        self.btnPasaBajas = tk.Button(root, text="PASA-BAJAS", bg="gray20", fg="DeepSkyBlue", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.showPasaBajas)
        self.btnPasaBajas.place(x=50, y=580, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón pasa-altas llama a la función "showPasaAltas" que muestra la imágen después del filtro pasa-altas.
        self.btnPasaAltas = tk.Button(root, text="PASA-ALTAS", bg="gray20", fg="DeepSkyBlue", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.showPasaAltas)
        self.btnPasaAltas.place(x=50, y=670, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #El botón pasa-bajas llama a la función "showEliminaBanda" que muestra la imágen después del filtro elimina-banda.
        self.btnEliminaBanda = tk.Button(root, text="ELIMINA-BANDA", bg="gray20", fg="DeepSkyBlue", font=("Times New Roman", 25, "italic"), borderwidth="2", relief="raised", command=self.showEliminaBanda)
        self.btnEliminaBanda.place(x=50, y=760, width=350) #Esto solo establece la posición del botón y el tamaño del ancho.

        #Botón de información.
        self.btnInfo = tk.Button(root, text="i", bg="gray20", fg="white", font=("Times New Roman", 15), borderwidth="2", relief="raised", command=self.showInfo)
        self.btnInfo.place(x=1090, y=790) #Esto solo establece la posición del botón y deja el tamaño por defecto de la letra.

        #ATRIBUTOS.

        self.umbral = None #Inicializamos el umbral en cero, puede ser modificado desde la aplicación.
        self.ancho = None #Inicializamos el ancho en cero, puede ser modificado desde la aplicación.
        self.centro = None #Inicializamos el centro en cero, puede ser modificado desde la aplicación.
        self.imagen = None #Inicializamos este atributo para guardar la imagen que vamos a cargar.
        self.espectro = None #Aquí se almacenará el espectro de frecuencias.
        self.imagenPasaBajas = None #Aquí se almacenará la imágen con el filtro pasa-bajas aplicado.
        self.imagenPasaAltas = None #Aquí se almacenará la imágen con el filtro pasa-altas aplicado.
        self.imagenEliminaBanda = None #Aquí se almacenará la imágen con el filtro elimina-banda aplicado.
        self.centeredFourierTransform = None #Aqui se almacenará la transformada centrada.
        self.currentImage = None #Inicializamos este atributo para facilitar la implementación de savePicture.
        self.currentFilter = None  # Inicializamos este atributo para facilitar la implementación de showInfo.

        #Estos atributos servirán para el manejo del umbral, el ancho y la posición del centro a ingresar.
        self.maxWidth = None
        self.maxHeight = None

        #Configuración del espacio para las gráficas.
        self.figure = Figure(figsize=(8, 6), dpi=100) #Establece el tamaño de la gráfica y los puntos por pulgada.
        self.figure.patch.set_facecolor("#141414") #Establece el color del fondo en gray8 para que se vea homogéneo.
        self.canvas = FigureCanvasTkAgg(self.figure, master=self.root) #Mete la gráfica a la ventana principal.
        self.canvas.get_tk_widget().place(x=460, y=120, width=1000, height=650) #Establece el tamaño y posición de la gráfica.

    #FUNCIONES DE MANEJO.

    def setUmbral(self):
        numero = simpledialog.askinteger("UMBRAL", "INGRESA EL UMBRAL:", minvalue=0, maxvalue=100) #Abre un cuadro de diálogo que solicita un entero entre 0 y 100 para guardarlo en numero.
        if numero is not None: #Valida que se haya introducido un número.
            self.umbral = numero #Establece numero como el nuevo umbral.
            self.updatePicture()

    def setAncho(self):
        numero = simpledialog.askinteger("ANCHO", "INGRESA EL ANCHO:", minvalue=0, maxvalue=100) #Abre un cuadro de diálogo que solicita un entero entre 0 y 100 para guardarlo en numero.
        if numero is not None: #Valida que se haya introducido un número.
            self.ancho = numero #Establece numero como el nuevo ancho.
            self.updatePicture()

    def setCentro(self):
        if self.imagen is None:
            messagebox.showwarning("Advertencia", "Cargue una imágen antes de establecer el centro.")
            return
        x = simpledialog.askinteger("COORDENADA X", "INGRESA LA COORDENADA X:", parent=self.root, minvalue=0, maxvalue=self.maxWidth)
        if x is not None:  #Verifica que se haya introducido un valor
            y = simpledialog.askinteger("COORDENADA Y", "INGRESA LA COORDENADA Y:", parent=self.root, minvalue=0, maxvalue=self.maxHeight)
            if y is not None:  #Verifica que se haya introducido un valor
                self.centro = (x,y)  #Establece el centro según las coordenadas establecidas.
                self.updatePicture()

    def showInfo(self): #Ya me dió flojera comentar, lol, pero básicamente aquí hacemos un switch para el correcto funcionamiento (Y polimorfismo) del botón showInfo.
        if self.imagen is None: #Si no hay imágen, mostramos recomendaciones, si sí la hay, damos la descripción de la misma y de los cambios realizados, ya sea la imágen original, el espectro de frecuencias o la imágen con algún filtro aplicado.
            messagebox.showinfo("INFORMACIÓN", "Antes de comenzar, considere las siguientes recomendaciones.\n\n* Cargue una imágen en formato .png, .jpg o .jpeg.\n* Establezca el umbral deseado para la aplicación de los filtros pasa-altas y pasa-bajas.\n* Establezca el ancho y centro deseados para el filtro elimina-banda.")
            return
        elif self.currentFilter == 'IMÁGEN ORIGINAL':
            messagebox.showinfo("ORIGINAL","Esta es la imágen original, pero en escala de grises.")
            return
        elif self.currentFilter == 'ESPECTRO DE FRECUENCIAS':
            messagebox.showinfo("ESPECTRO DE FRECUENCIAS","Este es el espectro de frecuencias.\n\nEn realidad se trata de la transformada de fourier bidimensional de la imágen, pero con las ondas más bajas al centro.")
            return
        elif self.currentFilter == 'FILTRO PASA-BAJAS':
            messagebox.showinfo("PASA-BAJAS","Este es el filtro pasa-bajas.\n\nPermite pasar solo las frecuencias bajas, y atenúa las frecuencias altas según el umbral establecido.\n\nEste filtro permite eliminar detalles finos, ya que están asociados a las frecuencias bajas.\n\nConsidere que entre mayor sea el umbral, menor será el efecto del filtro.")
            return
        elif self.currentFilter == 'FILTRO PASA-ALTAS':
            messagebox.showinfo("PASA-ALTAS","Este es el filtro pasa-altas.\n\nPermite pasar solo las frecuencias altas, y atenúa las frecuencias bajas según el umbral establecido.\n\nEste filtro permite resaltar bordes y texturas, ya que están asociados a las frecuencias altas.\n\nConsidere que entre mayor sea el umbral, mayor será el efecto del filtro.")
            return
        elif self.currentFilter == 'FILTRO ELIMINA-BANDA':
            messagebox.showinfo("ELIMINA-BANDA","Este es el filtro elimina-banda.\n\nNo permite el paso de las frecuencias cercanas al centro dado por el usuario, pero permite el paso del resto de frecuencias, sin importar si son altas o bajas según el ancho establecido.\n\nEste filtro permite suprimir patrones específicos.\n\nConsidere que entre mayor sea el ancho, mayor será el efecto del filtro.")
            return


    def loadPicture(self):
        if self.imagen is not None: #Verifica si hay alguna imágen cargada, en caso de que sí, lanza una advertencia y termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Ya hay una imagen cargada, elimínela para cargar otra.")
            return
        picturePath = filedialog.askopenfilename(filetypes=[("Archivos de imagen", "*.jpg *.jpeg *.png")]) #Si no hay imágen cargada, abre un cuadro de diálogo que solicita cargar una imágen, y la guarda en picturePath.
        if picturePath and "OneDrive" not in picturePath: #Verifica que se haya cargado algún archivo local, en caso de que sí, se procede.
            self.imagen = cv2.imread(picturePath, cv2.IMREAD_GRAYSCALE) #Se guarda la imágen cargada en self.imagen y luego se le aplica un filtro en escala de grises.
            self.showDimension() #Se muestran las dimensiones.
            self.showOriginal() #Se muestra la imágen original.
            self.createEspectro() #Se aplica la transformada de fourier a la imágen original.
        else:
            messagebox.showerror("Ruta inválida", "Verifique que la imágen se encuentre en el dispositivo.")
            return

    def showDimension(self):
        self.maxWidth = self.imagen.shape[1]  # Obtenemos el ancho máximo, como parámetro para setCentro y como dato de guía al usuario.
        self.maxHeight = self.imagen.shape[0]  # Obtenemos la altura máxima, como parámetro para setCentro y como dato de guía al usuario.

        # Con este label solo mostramos las dimensiones de la imágen cargada.
        self.root.showDimension = tk.Label(root, text=str(self.maxWidth) + " x " + str(self.maxHeight), bg="gray8", fg="white", font=("Times New Roman", 15, "bold"))
        self.root.showDimension.place(x=1120, y=790)  # Establece la posición del label y deja su tamaño por defecto.

    def savePicture(self):
        if self.imagen is None: #Verifica que haya alguna imágen cargada.
            messagebox.showwarning("Advertencia", "No hay ninguna imagen cargada.") #En caso de que no, lanza un aviso de que no hay imágen y termina la ejecución de la función.
            return
        elif self.currentFilter == 'ESPECTRO DE FRECUENCIAS': #Le damos un trato especial al espectro de frecuencias para que no se guarde la imágen negra.
            picturePath = filedialog.asksaveasfilename(defaultextension=".png", filetypes=[("PNG files", "*.png"), ("All files", "*.*")])  # Si sí hay imágen, solicitamos la ruta de guardado y la guardamos en picturePath.
            if picturePath:  # Si se estableció una ruta de guardado, procedemos.
                cv2.imwrite(picturePath, cv2.normalize(self.espectro, None, 0, 255, cv2.NORM_MINMAX))  # Con cv2, guardamos la imágen en la ruta establecida, después de aplicar cierto filtro.
        else:
            picturePath = filedialog.asksaveasfilename(defaultextension=".png", filetypes=[("PNG files", "*.png"), ("All files", "*.*")]) #Si sí hay imágen, solicitamos la ruta de guardado y la guardamos en picturePath.
            if picturePath: #Si se estableció una ruta de guardado, procedemos.
                cv2.imwrite(picturePath, self.currentImage) #Con cv2, gu    ardamos la imágen en la ruta establecida.

    def deletePicture(self):
        if self.imagen is None: #Verifica que haya alguna imágen cargada.
            messagebox.showwarning("Advertencia", "No hay ninguna imagen cargada.") #En caso de que no, lanza un aviso de que no hay imágen y termina la ejecución de la función.
            return
        else: #En caso de que sí, resetea todos los atributos que guardan imágenes y limpia el lienzo de la gráfica, incluyendo la eliminación del label de las dimensiones.
            self.resetAttributes()

    def resetAttributes(self):
        self.imagen = None
        self.centeredFourierTransform = None
        self.espectro = None
        self.imagenPasaBajas = None
        self.imagenPasaAltas = None
        self.imagenEliminaBanda = None
        self.root.showDimension.destroy()
        self.figure.clear()
        self.canvas.draw()

    def updatePicture(self): #Esta función fue creada con fines de actualización automática al cambiar el umbral, el centro o el ancho.
        if self.currentFilter == 'FILTRO PASA-BAJAS':
            self.showPasaBajas()
        elif self.currentFilter == 'FILTRO PASA-ALTAS':
            self.showPasaAltas()
        elif self.currentFilter == 'FILTRO ELIMINA-BANDA':
            self.showEliminaBanda()

    #FUNCIONES PARA EL FILTRADO.

    def createEspectro(self): #Básicamente solo guarda el resultado de la transformada bidimensional.
        self.fourierTransform() #Para eso llama a la función que hace la chamba.
        self.espectro = np.log(np.abs(self.centeredFourierTransform) + 1)   #Y guarda el resultado luego de aplicar dos cosas:
                                                                            #El valor absoluto para el manejo de los valores complejos resultantes de la transformada.
                                                                            #El '+1', que garantiza evitar el logaritmo de cero al momento de guardar el espectro en su forma más fácil de visualizar.

    def createImagenPasaBajas(self):
        filteredFourierTransform = self.pasaBajasCalc(self.centeredFourierTransform, self.umbral) #Aplica el cálculo del filtro pasa-bajas a la matriz centrada de frecuencias y la guarda en filteredFourierTransform.
        self.imagenPasaBajas = self.reconstructPicture(filteredFourierTransform) #Reconstruye la imágen y la guarda en su respectivo atributo.

    def createImagenPasaAltas(self):
        filteredFourierTransform = self.pasaAltasCalc(self.centeredFourierTransform, self.umbral) #Aplica el cálculo del filtro pasa-altas a la matriz centrada de frecuencias y la guarda en filteredFourierTransform.
        self.imagenPasaAltas = self.reconstructPicture(filteredFourierTransform) #Reconstruye la imágen y la guarda en su respectivo atributo.

    def createImagenEliminaBanda(self):
        filteredFourierTransform = self.eliminaBandaCalc(self.centeredFourierTransform, self.ancho) #Aplica el cálculo del filtro elimina-banda a la matriz centrada de frecuencias y la guarda en filteredFourierTransform.
        self.imagenEliminaBanda = self.reconstructPicture(filteredFourierTransform) #Reconstruye la imágen y la guarda en su respectivo atributo.

    def fourierTransform(self): #Aquí ocurre la magia chavales, esta función realiza la transformada de fourier de la imágen y la centra.
        f_transform = np.fft.fft2(self.imagen) #np.fft.fft2 aplica la transformada de fourier bidimensional a la imágen y la guarda en f_transform.
        self.centeredFourierTransform = np.fft.fftshift(f_transform) #np.fft.fftshift centra las bajas frecuencias de la transformada de Fourier en la imagen transformada y guarda la matriz en centeredFourierTransform.

    def pasaBajasCalc(self, centeredFourierTransform, umbral):
        filas, columnas = centeredFourierTransform.shape #Primero obtenemos las dimensiones de la matriz y las guardamos en las variables 'filas' y 'columnas'.
        cx, cy = columnas // 2, filas // 2 #Calculamos el centro de la matriz centrada y guardamos estos datos en 'cx' y 'cy' respectivamente.
        filtro = np.zeros_like(centeredFourierTransform) #Creamos un nuevo arreglo con las mismas dimensiones y tipo que centeredFourierTransform, pero con todos sus elementos inicializados a cero.
        filtro[cy-umbral:cy+umbral, cx-umbral:cx+umbral] = 1    #Definimos un rango del tamaño del umbral centrado en las coordenadas [cx,cy] y establecemos los valores de los píxeles dentro de este rango a 1.
                                                                #Así creamos una región cuadrada de unos en el centro de una matriz de ceros.
                                                                #Esta región definirá el área de frecuencias que serán permitidas por el filtro.
        return centeredFourierTransform * filtro        #Multiplicamos elemento por elemento la matriz de la transformada de Fourier centrada con el filtro.
                                                        #Así solo las frecuencias dentro del rango definido por el umbral serán retenidas, todas las demás serán eliminadas.

    #En este caso, el filtro permite pasar solo las frecuencias bajas (Cercanas al centro), y atenúa las frecuencias altas (Las más alejadas del centro), según el umbral establecido.
    #Esto permite eliminar detalles finos, asociados a las frecuencias bajas.

    def pasaAltasCalc(self, centeredFourierTransform, umbral):
        filas, columnas = centeredFourierTransform.shape #Primero obtenemos las dimensiones de la matriz y las guardamos en las variables 'filas' y 'columnas'.
        cx, cy = columnas // 2, filas // 2 #Calculamos el centro de la matriz centrada y guardamos estos datos en 'cx' y 'cy' respectivamente.
        filtro = np.ones_like(centeredFourierTransform) #Creamos un nuevo arreglo con las mismas dimensiones y tipo que centeredFourierTransform, pero con todos sus elementos inicializados a uno.
        filtro[cy-umbral:cy+umbral, cx-umbral:cx+umbral] = 0    #Definimos un rango del tamaño del umbral centrado en las coordenadas [cx,cy] y establecemos los valores de los píxeles dentro de este rango a 0.
                                                                #Así creamos una región cuadrada de ceros en el centro de una matriz de unos.
                                                                #Esta región definirá el área de frecuencias que serán eliminados por el filtro.
        return centeredFourierTransform * filtro        #Multiplicamos elemento por elemento la matriz de la transformada de Fourier centrada con el filtro.
                                                        #Así solo las frecuencias fuera del rango definido por el umbral serán retenidas, todas las demás serán eliminadas.

    #En este caso, el filtro no permite el paso de las frecuencias bajas (Cercanas al centro), pero permite el paso de las frecuencias altas (Las más alejadas del centro), según el umbral establecido.
    #Esto permite resaltar bordes y texturas, asociados a las frecuencias altas.

    def eliminaBandaCalc(self, centeredFourierTransform, ancho):
        cx, cy = self.centro #Primero establecemos el centro sobre el cual aplicaremos el umbral como el centro establecido por usuario.
        filtro = np.ones_like(centeredFourierTransform) #Creamos un nuevo arreglo con las mismas dimensiones y tipo que centeredFourierTransform, pero con todos sus elementos inicializados a uno.
        filtro[cy-ancho:cy+ancho, cx-ancho:cx+ancho] = 0    #Definimos un rango del tamaño del umbral centrado en las coordenadas del centro dado por el usuario y establecemos los valores de los píxeles dentro de este rango a 0.
                                                            #Así creamos una región cuadrada de ceros en el centro dado por el usuario de una matriz de unos.
                                                            #Esta región definirá el área de frecuencias que serán eliminados por el filtro.
        return centeredFourierTransform * filtro        #Multiplicamos elemento por elemento la matriz de la transformada de Fourier centrada con el filtro.
                                                        #Así solo las frecuencias fuera del rango definido por el umbral serán retenidas, todas las demás serán eliminadas.

    #En este caso, el filtro no permite el paso de las frecuencias cercanas al centro dado por el usuario, pero permite el paso del resto de frecuencias, sin importar si son altas o bajas según el ancho establecido.
    #Esto permite suprimir patrones específicos.

    #FUNCIONES PARA MOSTRAR IMÁGENES.

    def plotImage(self, img, title):
        self.currentImage = img #Establecemos la imagen que se está mostrando como la actual, para facilitar el guardado.
        self.currentFilter = title  #Establecemos el nombre del filtro que se está mostrando como currentFilter, para facilitar la implementación de showInfo.
        self.figure.clear() #Limpiamos la figura actual para evitar superposiciones de figuras anteriores.
        ax = self.figure.add_subplot(111) #Añadimos una sola área de gráficos a la figura.
        ax.imshow(img, cmap='gray') #Mostramos la imágen recibida como primer parámetro en escala de grises.
        ax.set_title(title, color='white') #Mostramos el título recibido como segundo parámetro en color blanco.
        ax.tick_params(axis='x', colors='white') #Personalizamos el color de las marcas del eje x con el color blanco.
        ax.tick_params(axis='y', colors='white') #Personalizamos el color de las marcas del eje y con el color blanco.
        self.canvas.draw() #Actualizamos el canvas para que muestre la figura.

    def showOriginal(self):
        if self.imagen is None: #Verificamos si hay alguna imágen cargada, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Cargue una imagen primero.")
            return
        self.plotImage(self.imagen, 'IMÁGEN ORIGINAL') #En caso de que sí, mostramos la imágen original.

    def showEspectro(self):
        if self.espectro is None: #Verificamos si el espectro de frecuencias está creado, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Cargue una imagen primero.")
            return
        self.plotImage(self.espectro, 'ESPECTRO DE FRECUENCIAS') #En caso de que sí, mostramos el espectro de frecuencias.

    def reconstructPicture(self, filteredFourierTransform):
        inverseFourierTransform = np.fft.ifftshift(filteredFourierTransform) #Deshacemos el centrado de la transformada de fourier realizado por np.fft.fftshift
        reconstructedPicture = np.fft.ifft2(inverseFourierTransform) #Aplicamos la transformada inversa de fourier bidimensional para convertir la imagen de vuelta al dominio espacial desde el dominio de la frecuencia.
        reconstructedPicture = np.abs(reconstructedPicture) #Tomamos el valor absoluto para obtener la magnitud real de la imagen reconstruida, así evitamos los valores complejos que pueda soltar la transformada inversa.
        return reconstructedPicture #Regresamos la imagen reconstruida.

    def showPasaBajas(self):
        if self.imagen is None: #Verificamos si hay alguna imágen cargada, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Cargue una imagen primero.")
            return
        if self.umbral is None: #Verificamos si el umbral está establecido, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Establezca el umbral primero.")
            return
        self.createImagenPasaBajas() #Creamos la imágen filtrada con el filtro pasa-bajas.
        self.plotImage(self.imagenPasaBajas, 'FILTRO PASA-BAJAS') #Mostramos la imagen filtrada con pasa-bajas en el lienzo.

    def showPasaAltas(self):
        if self.imagen is None: #Verificamos si hay alguna imágen cargada, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Cargue una imagen primero.")
            return
        if self.umbral is None: #Verificamos si el umbral está establecido, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Establezca el umbral primero.")
            return
        self.createImagenPasaAltas() #Creamos la imágen filtrada con el filtro pasa-altas.
        self.plotImage(self.imagenPasaAltas, 'FILTRO PASA-ALTAS') #Mostramos la imagen filtrada con pasa-altas en el lienzo.

    def showEliminaBanda(self):
        if self.imagen is None: #Verificamos si hay alguna imágen cargada, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Cargue una imagen primero.")
            return
        if self.ancho is None: #Verificamos si el ancho está establecido, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Establezca el ancho primero.")
            return
        if self.centro is None: #Verificamos si el centro está establecido, en caso de que no, lanzamos una advertencia y se termina la ejecución de la función.
            messagebox.showwarning("Advertencia", "Establezca el centro primero.")
            return
        self.createImagenEliminaBanda() #Creamos la imágen filtrada con el filtro elimina-banda.
        self.plotImage(self.imagenEliminaBanda, 'FILTRO ELIMINA-BANDA') #Mostramos la imagen filtrada con elimina-banda en el lienzo.

if __name__ == "__main__":
    root = tk.Tk() #Creamos una nueva instancia de la ventana principal de Tkinter.
    app = Fourier(root) #Inicializamos 'Fourier' pasando dicha ventana principal como argumento.
    root.mainloop() #Iniciamos el bucle de eventos, permitiendo que la ventana se mantenga abierta y responda a eventos.
