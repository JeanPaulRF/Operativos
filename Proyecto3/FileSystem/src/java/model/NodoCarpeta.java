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
import java.util.List;

public class NodoCarpeta extends Nodo{
    public List<NodoCarpeta> Carpetas;
    public List<NodoArchivo> Archivos;
    public NodoCarpeta Padre;
    
    public NodoCarpeta(String nombre){
        super(nombre, "Carpeta");
        // El nodo padre podria ser null, al ser el primero
        this.Padre = null;
        this.Carpetas = new ArrayList<>();
        this.Archivos = new ArrayList<>();
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
    
    public void crearNuevaCarpeta(String nombreCarpeta){
        // Verificar si el nombre de la carpeta ya existe
        if (existeCarpeta(nombreCarpeta)) {
            System.out.println("El nombre de la carpeta ya existe. No se puede crear.");
            return;
        }
        
        // Crear un nuevo nodo carpeta
        NodoCarpeta nuevaCarpeta = new NodoCarpeta(nombreCarpeta);
        
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
    
    public void crearNuevoArchivo(String nombreArchivo){
        // Verificar si el nombre del archivo ya existe
        if (existeArchivo(nombreArchivo)) {
            System.out.println("El nombre del archivo ya existe. No se puede crear.");
            return;
        }
        
        // Crear un nuevo nodo archivo
        NodoArchivo nuevoArchivo = new NodoArchivo(nombreArchivo);
        
        // Agregar el nuevo archivo a la lista de carpetas
        agregarArchivo(nuevoArchivo);

        System.out.println("Archivo creado exitosamente.");
    }
    
    public void asignarPadre(NodoCarpeta newPadre){
        this.Padre = newPadre;
    }
}
