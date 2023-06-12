/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package graphNodes;

/**
 *
 * @author david
 */
public class NodoArchivo extends Nodo {
    private String nombreArchivo;
    
    public NodoArchivo(String nombre, String nombArch) {
        super(nombre, "Archivo");
        this.nombreArchivo = nombArch;
    }
    
    public String getNombreArchivo() {
        return nombreArchivo;
    }
    
    public void setNombreArchivo(String nombreArch){
        this.nombreArchivo = nombreArch;
    }
}
