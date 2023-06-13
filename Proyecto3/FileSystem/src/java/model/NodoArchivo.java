/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author david
 */
public class NodoArchivo extends Nodo {
    private String pathArchivo;
    private List<NodoUsuario> usuariosCompartido;
    
    public NodoArchivo(String nombre) {
        super(nombre, "Archivo");
        this.pathArchivo = "/" + nombre;
        this.usuariosCompartido = new ArrayList<>();
    }
    
    public String getPathArchivo() {
        return pathArchivo;
    }
    
    public void setPathArchivo(String pathArch){
        this.pathArchivo = pathArch;
    }
}
