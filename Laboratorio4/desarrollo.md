# Pary Joaquin Andres 41786697

## Laboratorio 4 MyShellBasic

## Modos de Uso
El programa se podra compilar con los requerimientos pedidos utilizando el comando **make** y se podra eliminar el ejecutable con el comando **clean**, una vez ejecutado se podran utilizar los siguientes comandos:
* **./lab4 -path** : Si al ejecutar el programa se agrega como argumento la direccion de un archivo de texto, se ejecutara los comando que esten dentro del archivo de texto. La direccion puede ser relativa o absoluta, despues de ejecutar los comandos se cerrara el programa. Si se ejecuta sin path el programa permitira ingresar comandos manualmente.
* **cd** :  Permite cambiar el directorio de trabajo, si se desea mover a un directorio mas bajo solo se permite uno a la vez, es decir no permite colocar **cd ..**.
*  **cd-** : Devuelve la ultima direccion de trabajo.
* **clr** : Limpia la pantalla.
* **echo 'texto'** : Imprime **texto** en la pantalla
* **quit** : Permite cerrar el programa
* Si se ingresa otro comando diferente a los mencionados la shell tambien lo podra ejecutar y de ser necesario permitira el uso de paths relativos y absolutos
* Al colocar un **&** al final de un comado, la shell lanzara al programa a ejecutarse en background.