/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author david
 */
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class NodoCarpeta extends Nodo{
    public List<NodoCarpeta> Carpetas;
    public List<NodoArchivo> Archivos;
    private String pathCarpeta;
    //public NodoCarpeta Padre;
    
    public NodoCarpeta(String nombre){
        super(nombre, "Carpeta");
        // El nodo padre podria ser null, al ser el primero
        //this.Padre = null;
        this.pathCarpeta = nombre + "/"; 
        this.Carpetas = new ArrayList<>();
        this.Archivos = new ArrayList<>();
    }
    
    // buscar un archivo dentro de una carpeta
    public NodoArchivo buscarArchivo(String path){
        // primero voy descomponiendo el path
        NodoArchivo archivoError = new NodoArchivo("No existe, error 101");
        
        //primero desgloso el path
        String[] partes = path.split("/");
        
        if (partes.length == 1){
            // quiere decir que estoy en el ultmo nivel de busqueda
            for (NodoArchivo archivo : Archivos) {
                if (archivo.getNombre().equals(partes[0])) {
                    return archivo;
                }
            }
            System.out.println("Error el archivo no existe.");
            return archivoError; // En caso de que no exista
        }
        else{
            // Si partes es > 1, entonces aun me falta profundizar
            for (NodoCarpeta carpeta :Carpetas){
                if (carpeta.getNombre().equals(partes[0])) {
                    // si encuentra una coincidencia, busca en la carpeta
                    String newpath = String.join("/", Arrays.copyOfRange(partes, 1, partes.length));
                    return carpeta.buscarArchivo(newpath);
                }
            }
            // no lo encontro
            System.out.println("Error en el path. La carpeta no existe en el usuario");
            return archivoError;
        }
    }
    
    public NodoCarpeta buscarCarpeta(String path){
        NodoCarpeta carpetaError = new NodoCarpeta("No existe, error 102");
        
        // Primero partimos el path
        String[] partes = path.split("/");
        
        // si el path es de uno ya estamos en el nivel
        if (partes.length == 1){
            
            for (NodoCarpeta carpeta : Carpetas) {
                if (carpeta.getNombre().equals(partes[0])) {
                    return carpeta;
                }
            }
            System.out.println("Error la carpeta no existe.");
            return carpetaError; // En caso de que no exista
        }
        else if(partes.length > 1){
            // Si es mayor que 1, la primera parte es la primera carpeta
            // aqui es recursiva
            for (NodoCarpeta carpeta :Carpetas){
                if (carpeta.getNombre().equals(partes[0])) {
                    // si encuentra una coincidencia, busca en la carpeta
                    String newpath = String.join("/", Arrays.copyOfRange(partes, 1, partes.length));
                    return carpeta.buscarCarpeta(newpath);
                }
            }
            // no lo encontro
            System.out.println("Error en el path. La carpeta no existe en el usuario");
            return carpetaError;
        }
        else{
            System.out.println("Error en el path.");
            return carpetaError;
        }
    }
    
    public void agregarCarpeta(NodoCarpeta newCarpeta) {
        Carpetas.add(newCarpeta);
    }
    
    public boolean existeCarpeta(String nombreCarpeta) {
        for (NodoCarpeta carpeta : Carpetas) {
            if (carpeta.getNombre().equals(nombreCarpeta)) {
                return true; // El nombre de la carpeta ya existe
            }
        }
        return false; // El nombre de la carpeta no existe
    }
    
    // para cuando se crea una carpeta, estando dentro de otra carpeta
    //   se llamaria a la funcion con un getPathCarpeta(), nuevacarpeta
    public void crearNuevaCarpeta(String pathPadre, String nombreCarpeta){
        // Verificar si el nombre de la carpeta ya existe
        if (existeCarpeta(nombreCarpeta)) {
            System.out.println("El nombre de la carpeta ya existe. No se puede crear.");
            return;
        }
        
        // Crear un nuevo nodo carpeta
        NodoCarpeta nuevaCarpeta = new NodoCarpeta(nombreCarpeta);
        
        // Establezco el nuevo path, añadiendo al padre
        //   este primer getPathCarpeta no estaria contaminado: nombre/
        String nuevoPath = pathPadre + getPathCarpeta();
        setPathCarpeta(nuevoPath);
        
        // Agregar la nueva carpeta a la lista de carpetas
        agregarCarpeta(nuevaCarpeta);

        System.out.println("Carpeta creada exitosamente.");
    }
    
    public void agregarArchivo(NodoArchivo newArchivo) {
        Archivos.add(newArchivo);
    }
    
    public boolean existeArchivo(String nombreArchivo) {
        for (NodoArchivo archivo : Archivos) {
            if (archivo.getNombre().equals(nombreArchivo)) {
                return true; // El nombre del archivo ya existe
            }
        }
        return false; // El nombre del archivo no existe
    }
    
    // para cuando se crea un archivo, estando dentro de otra carpeta
    //   se llamaria a la funcion con un getPathCarpeta(), nuevoArchivo
    public void crearNuevoArchivo(String pathPadre, String nombreArchivo){
        // Verificar si el nombre del archivo ya existe
        if (existeArchivo(nombreArchivo)) {
            System.out.println("El nombre del archivo ya existe. No se puede crear.");
            return;
        }
        
        // Crear un nuevo nodo archivo
        NodoArchivo nuevoArchivo = new NodoArchivo(nombreArchivo);
        
        // Creo el path para el archivo
        String nuevoPath = pathPadre + nuevoArchivo.getPathArchivo();
        nuevoArchivo.setPathArchivo(nuevoPath);
        
        // Agregar el nuevo archivo a la lista de carpetas
        agregarArchivo(nuevoArchivo);

        System.out.println("Archivo creado exitosamente.");
    }
    
    public String getPathCarpeta() {
        return pathCarpeta;
    }
    
    public void setPathCarpeta(String pathCarp){
        this.pathCarpeta = pathCarp;
    }
    
    public ArrayList<String> listarDirectorio() {
        ArrayList<String> contenido = new ArrayList<>();
        contenido.add("CARPETAS:");
        
        for(NodoCarpeta carpeta :Carpetas) {
            contenido.add(carpeta.getNombre());
        }
        
        contenido.add("ARCHIVOS:");
        
        for(NodoArchivo archivo :Archivos) {
            contenido.add(archivo.getNombre());
        }
        
        return contenido;
    }
}
