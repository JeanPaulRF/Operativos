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
    
    public void agregarArchivo(NodoArchivo newArchivo) {
        Archivos.add(newArchivo);
    }
    
    public void asignarPadre(NodoCarpeta newPadre){
        this.Padre = newPadre;
    }
}
